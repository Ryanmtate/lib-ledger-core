// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from stellar_like_wallet.djinni

#include "StellarLikeFeeStats.hpp"  // my header
#include "Marshal.hpp"

namespace djinni_generated {

StellarLikeFeeStats::StellarLikeFeeStats() = default;

StellarLikeFeeStats::~StellarLikeFeeStats() = default;

auto StellarLikeFeeStats::fromCpp(JNIEnv* jniEnv, const CppType& c) -> ::djinni::LocalRef<JniType> {
    const auto& data = ::djinni::JniClass<StellarLikeFeeStats>::get();
    auto r = ::djinni::LocalRef<JniType>{jniEnv->NewObject(data.clazz.get(), data.jconstructor,
                                                           ::djinni::get(::djinni::I64::fromCpp(jniEnv, c.lastBaseFee)),
                                                           ::djinni::get(::djinni::I64::fromCpp(jniEnv, c.modeAcceptedFee)),
                                                           ::djinni::get(::djinni::I64::fromCpp(jniEnv, c.minAccepted)),
                                                           ::djinni::get(::djinni::I64::fromCpp(jniEnv, c.maxFee)))};
    ::djinni::jniExceptionCheck(jniEnv);
    return r;
}

auto StellarLikeFeeStats::toCpp(JNIEnv* jniEnv, JniType j) -> CppType {
    ::djinni::JniLocalScope jscope(jniEnv, 5);
    assert(j != nullptr);
    const auto& data = ::djinni::JniClass<StellarLikeFeeStats>::get();
    return {::djinni::I64::toCpp(jniEnv, jniEnv->GetLongField(j, data.field_lastBaseFee)),
            ::djinni::I64::toCpp(jniEnv, jniEnv->GetLongField(j, data.field_modeAcceptedFee)),
            ::djinni::I64::toCpp(jniEnv, jniEnv->GetLongField(j, data.field_minAccepted)),
            ::djinni::I64::toCpp(jniEnv, jniEnv->GetLongField(j, data.field_maxFee))};
}

}  // namespace djinni_generated