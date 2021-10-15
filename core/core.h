#ifndef CORE_H
#define CORE_H

#include <napi.h>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#define NOMINMAX
#include <windows.h>
#else
#include <dlfcn.h>
#define LoadLibrary(path) dlopen(path, RTLD_LAZY)
#define GetProcAddress(handler, func_name) dlsym(handler, func_name);
#define FreeLibrary(handler) dlclose(handler);
typedef void* HMODULE;
typedef void* FARPROC;
#endif

typedef bool (*INIT)(char *root_dir_path, bool use_gpu);
typedef const char *(*RETURN_CHAR)();
typedef bool (*YUKARIN_S)(int length, int64_t *phoneme_list, int64_t *speaker_id, float *output);
typedef bool (*YUKARIN_SA)(
    int length,
    int64_t *vowel_phoneme_list,
    int64_t *consonant_phoneme_list,
    int64_t *start_accent_list,
    int64_t *end_accent_list,
    int64_t *start_accent_phrase_list,
    int64_t *end_accent_phrase_list,
    int64_t *speaker_id,
    float *output
);
typedef bool (*DECODE)(
    int length,
    int phoneme_size,
    float *f0,
    float *phoneme,
    int64_t *speaker_id,
    float *output
);


class Core {
public:
    Core(const std::string core_file_path, std::string root_dir_path, bool use_gpu);
    ~Core();

    const char *metas();

    bool yukarin_s_forward(int length, int64_t *phoneme_list, int64_t *speaker_id, float *output);

    bool yukarin_sa_forward(
        int length,
        int64_t *vowel_phoneme_list,
        int64_t *consonant_phoneme_list,
        int64_t *start_accent_list,
        int64_t *end_accent_list,
        int64_t *start_accent_phrase_list,
        int64_t *end_accent_phrase_list,
        int64_t *speaker_id,
        float *output
    );

    bool decode_forward(
        int length,
        int phoneme_size,
        float *f0,
        float *phoneme,
        int64_t *speaker_id,
        float *output
    );

    const char *last_error_message();

private:
    HMODULE m_handler;
};

#endif // CORE_H
