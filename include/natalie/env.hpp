#pragma once

#include <setjmp.h>
#include <stdlib.h>

#include "natalie/forward.hpp"

namespace Natalie {

struct Env {
    Env() { }

    Env(Env *outer)
        : outer { outer } {
        global_env = outer->global_env;
    }

    Env(GlobalEnv *global_env)
        : global_env { global_env } { }

    static Env new_block_env(Env *, Env *);
    static Env new_detatched_block_env(Env *);

    const char *find_current_method_name();
    char *build_code_location_name(Env *location_env);

    Value *var_get(const char *, ssize_t);
    Value *var_set(const char *, ssize_t, bool, Value *);

    Value *raise(ClassValue *, const char *, ...);
    Value *raise_exception(ExceptionValue *);
    Value *raise_local_jump_error(Value *, const char *);

    GlobalEnv *global_env { nullptr };
    Vector *vars { nullptr };
    Env *outer { nullptr };
    Block *block { nullptr };
    bool block_env { false };
    bool rescue { false };
    jmp_buf jump_buf;
    ExceptionValue *exception { nullptr };
    Env *caller { nullptr };
    const char *file { nullptr };
    ssize_t line { 0 };
    const char *method_name { nullptr };
    Value *match { nullptr };
};

}
