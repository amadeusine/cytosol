/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


typedef enum cyt_RunResult {
        MadeProgress,
        NoProgress,
} cyt_RunResult;

typedef struct cyt_CellEnv cyt_CellEnv;

typedef struct cyt_driver_runner cyt_driver_runner;

typedef struct cyt_ExecutionState cyt_ExecutionState;

typedef struct cyt_program cyt_program;

typedef struct cyt_value cyt_value;

typedef struct cyt_record_id {
        uint32_t _0;
        size_t _1;
} cyt_record_id;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct cyt_program *cyt_program_new(void);

void cyt_program_destroy(struct cyt_program *prog);

/**
 * # Safety
 * `name` must be a valid pointer to a UTF-8 and NUL-terminated string.
 */
bool cyt_program_record_by_name(const struct cyt_program *prog,
                                const char *name,
                                struct cyt_record_id *out_id);

struct cyt_driver_runner *cyt_driver_runner_new(void);

void cyt_driver_runner_destroy(struct cyt_driver_runner *driver_runner);

/**
 * # Safety
 * `name` and `source` must be pointers to valid UTF-8 and NUL-terminated strings.
 */
void cyt_driver_runner_add_file_from_string(struct cyt_driver_runner *r,
                                            const char *name,
                                            const char *source);

/**
 * If an error occurs `false` is returned.
 * In that case the error will also be directly written to stdout.
 * If no error occurs then `true` is returned.
 */
bool cyt_driver_runner_compile(struct cyt_driver_runner *r,
                               struct cyt_program *prog);

/**
 * Run the program for one single iteration.
 */
enum cyt_RunResult cyt_driver_runner_run_single_iteration(struct cyt_driver_runner *r,
                                                          const struct cyt_program *prog,
                                                          struct cyt_ExecutionState *exec_state,
                                                          struct cyt_CellEnv *cell_env);

/**
 * Run the program for multiple iterations.
 *
 * This runs the program until it either no longer makes progress or
 * the iteration bound was reached.
 *
 * An iteration bound of `0` means that there is no bound.
 */
void cyt_driver_runner_run(struct cyt_driver_runner *r,
                           const struct cyt_program *prog,
                           struct cyt_ExecutionState *exec_state,
                           struct cyt_CellEnv *cell_env,
                           size_t iter_bound);

struct cyt_value *cyt_value_new_integer(ptrdiff_t n);

/**
 * # Safety
 * `s` must be a valid pointer to a UTF-8 and NUL-terminated string.
 */
struct cyt_value *cyt_value_new_string(const char *s);

struct cyt_value *cyt_value_new_record(void);

/**
 * Adds the `new_field` value to the record in `record`.
 *
 * If `record` is not a value created with `cyt_value_new_record` then this function has no effect.
 *
 * The `new_field` value will transfer ownership, so the `destroy` function *must not* be called
 * on that value again.
 */
void cyt_value_record_add_field(struct cyt_value *record,
                                struct cyt_value *new_field);

void cyt_value_destroy(struct cyt_value *value);

/**
 * Get the integer value in `value` by writing it in `out_i`.
 *
 * If `value` is not an integer then `false` is returned, `true` otherwise.
 */
bool cyt_value_get_integer(const struct cyt_value *value, ptrdiff_t *out_i);

/**
 * Get the string value in `value` by writing a pointer to `out_ptr` and the length to `out_len`.
 *
 * The string is **NOT** NUL-terminated.
 *
 * If `value` is not a string then `false` is returned, `true` otherwise.
 */
bool cyt_value_get_string(const struct cyt_value *value,
                          const char **out_ptr,
                          size_t *out_len);

/**
 * Get a field value of the record in `value` at index `index` by creating a
 * copy of the field and writing it to `out_value`.
 *
 * The value in `out_value` will be owned, so the `destroy` function needs to
 * be called.
 *
 * If `value` is not a record or if `index` is out of bounds then `false` is
 * returned, `true` otherwise.
 */
bool cyt_value_get_record_field(const struct cyt_value *value,
                                size_t index,
                                const struct cyt_value **out_value);

struct cyt_CellEnv *cyt_cellenv_new(void);

void cyt_cellenv_destroy(struct cyt_CellEnv *cell_env);

/**
 * Add a record with id `record_id` to the environment `quantity` times.
 *
 * The `fields` will be copied
 *
 * # Safety
 * `fields` must be a valid pointer to an array of values allocated by the
 * `cyt_value_` functions with `num_fields` elements.
 */
void cyt_cellenv_add_record(struct cyt_CellEnv *cell_env,
                            size_t quantity,
                            struct cyt_record_id record_id,
                            size_t num_fields,
                            const struct cyt_value *const *fields);

struct cyt_ExecutionState *cyt_exec_state_new(void);

void cyt_exec_state_destroy(struct cyt_ExecutionState *exec_state);

/**
 * # Safety
 * `s` must be a valid pointer to a UTF-8 and NUL-terminated string.
 * `f` must be a valid function pointer.
 */
void cyt_exec_state_set_extern_function(struct cyt_ExecutionState *exec_state,
                                        const char *name,
                                        void (*f)(void*, size_t, const struct cyt_value*const *),
                                        void *data);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
