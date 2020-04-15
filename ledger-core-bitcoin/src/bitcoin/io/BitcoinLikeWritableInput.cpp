/*
 *
 * BitcoinLikeWritableInput.cpp
 * ledger-core
 *
 * Created by Pierre Pollastri on 10/04/2018.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Ledger
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <bitcoin/io/BitcoinLikeWritableInput.hpp>
#include <bitcoin/scripts/BitcoinLikeScript.hpp>
#include <bitcoin/scripts/BitcoinLikeInternalScript.hpp>

namespace ledger {
    namespace core {

        BitcoinLikeWritableInput::BitcoinLikeWritableInput(
                const std::shared_ptr<ledger::core::BitcoinLikeBlockchainExplorer> &explorer,
                const std::shared_ptr<api::ExecutionContext> &context, uint32_t sequence,
                const std::vector<std::vector<uint8_t> > &pubKeys,
                const std::vector<std::shared_ptr<api::DerivationPath>> &paths, const std::string &address,
                const std::shared_ptr<api::Amount> &amount, const std::string &previousTxHash, int32_t index,
                const std::vector<uint8_t> &scriptSig,
                const std::shared_ptr<api::BitcoinLikeOutput> &previousOutput,
                const std::string &keychainEngine) :
                _explorer(explorer), _context(context), _sequence(sequence),
                _pubKeys(pubKeys), _paths(paths), _address(address), _index(index),
                _amount(amount), _previousHash(previousTxHash),
                _previousScript(previousOutput) {
            // TODO handle the case where explorer, context are missing properly
            if (!scriptSig.empty()) {
                auto isSigned = true;
                auto strScriptSig = hex::toString(scriptSig);
                auto parsedScript = BitcoinLikeScript::parse(scriptSig,
                                                             BitcoinLikeScriptConfiguration(isSigned, keychainEngine));
                if (parsedScript.isSuccess()) {
                    _scriptSig = parsedScript.getValue();
                }
            }
        }

        optional<std::string> BitcoinLikeWritableInput::getAddress() {
            return Option<std::string>(_address).toOptional();
        }

        std::vector<std::vector<uint8_t>> BitcoinLikeWritableInput::getPublicKeys() {
            return _pubKeys;
        }

        std::vector<std::shared_ptr<api::DerivationPath> > BitcoinLikeWritableInput::getDerivationPath() {
            return _paths;
        }

        std::shared_ptr<api::Amount> BitcoinLikeWritableInput::getValue() {
            return _amount;
        }

        bool BitcoinLikeWritableInput::isCoinbase() {
            return false;
        }

        optional<std::string> BitcoinLikeWritableInput::getCoinbase() {
            return Option<std::string>().toOptional();
        }

        optional<std::string> BitcoinLikeWritableInput::getPreviousTxHash() {
            return Option<std::string>(_previousHash).toOptional();
        }

        optional<int32_t> BitcoinLikeWritableInput::getPreviousOutputIndex() {
            return Option<int32_t>(_index).toOptional();
        }

        std::shared_ptr<api::BitcoinLikeOutput> BitcoinLikeWritableInput::getPreviousOuput() {
            return _previousScript;
        }

        std::vector<uint8_t> BitcoinLikeWritableInput::getScriptSig() {
            return _scriptSig.serialize();
        }

        std::shared_ptr<api::BitcoinLikeScript> BitcoinLikeWritableInput::parseScriptSig() {
            return std::make_shared<BitcoinLikeInternalScript>(_scriptSig);
        }

        void BitcoinLikeWritableInput::setScriptSig(const std::vector<uint8_t> &scriptSig) {
            _scriptSig = BitcoinLikeScript::parse(scriptSig).getValue();
        }

        void BitcoinLikeWritableInput::pushToScriptSig(const std::vector<uint8_t> &data) {
            _scriptSig << data;
        }

        void BitcoinLikeWritableInput::setSequence(int32_t sequence) {
            _sequence = (uint32_t) sequence;
        }

        int64_t BitcoinLikeWritableInput::getSequence() {
            return (int32_t) _sequence;
        }

        void BitcoinLikeWritableInput::setP2PKHSigScript(const std::vector<uint8_t> &signature) {
            pushToScriptSig(signature);
            pushToScriptSig(_pubKeys[0]);
        }

        void BitcoinLikeWritableInput::getPreviousTransaction(const std::shared_ptr<api::BinaryCallback> & callback) {
            getPreviousTransaction().callback(_context, callback);
        }

        Future<std::vector<uint8_t>> BitcoinLikeWritableInput::getPreviousTransaction() {
            return _explorer->getRawTransaction(getPreviousTxHash().value()).map<std::vector<uint8_t> >(_context,
                                                                                                        [](const Bytes &bytes) {
                                                                                                            return bytes.getContainer();
                                                                                                        });
        }

    }
}