// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from thread_dispatcher.djinni

#ifndef DJINNI_GENERATED_RUNNABLE_HPP
#define DJINNI_GENERATED_RUNNABLE_HPP
#ifndef LIBCORE_EXPORT
    #if defined(_MSC_VER)
       #include <libcore_export.h>
    #else
       #define LIBCORE_EXPORT
    #endif
#endif

namespace ledger { namespace core { namespace api {

/**
 *Class representing a runnable object
 *A runnable, needs a specific execution context (refer to ExecutionContext) to run
 */
class LIBCORE_EXPORT Runnable {
public:
    virtual ~Runnable() {}

    /**Trigger runnable execution */
    virtual void run() = 0;
};

} } }  // namespace ledger::core::api
#endif //DJINNI_GENERATED_RUNNABLE_HPP