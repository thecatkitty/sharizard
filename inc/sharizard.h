#ifndef SHARIZARD_H
#define SHARIZARD_H

#include <sharizard/base.h>

enum shiz_result
{
    SHIZ_OK = 1 << 0,
    SHIZ_CANCEL = 1 << 1,
    SHIZ_INCOMPLETE = -1
};

enum
{
    SHIZM_INIT,
    SHIZM_ENTERED,
    SHIZM_NOTIFY,
    SHIZM_CHECK,
    SHIZM_NEXT,
};

enum
{
    SHIZFT_SEPARATOR,
    SHIZFT_LABEL,
    SHIZFT_TEXTBOX,
    SHIZFT_CHECKBOX,
    SHIZFT_OPTION,
    SHIZFT_BITMAP,
};

#define SHIZFF_STATIC  (0 << 0)
#define SHIZFF_DYNAMIC (1 << 0)

#define SHIZFF_LEFT   (0 << 1)
#define SHIZFF_CENTER (1 << 1)
#define SHIZFF_RIGHT  (2 << 1)
#define SHIZFF_ALIGN  (3 << 1)

#define SHIZFF_BODY     (0 << 3)
#define SHIZFF_FOOTER   (1 << 3)
#define SHIZFF_POSITION (1 << 3)

#define SHIZFF_UNCHECKED (0 << 3)
#define SHIZFF_CHECKED   (1 << 3)

typedef int(shiz_page_proc)(int msg, void *param, void *data);

typedef struct
{
    char       *buffer;
    size_t      capacity;
    size_t      length;
    const char *alert;
} shiz_textbox_data;

typedef struct
{
    int      type;
    int      flags;
    intptr_t data;
} shiz_field;

typedef struct
{
    int             title;
    shiz_page_proc *proc;
    void           *data;
    int             length;
    shiz_field     *fields;
} shiz_page;

extern bool
shiz_enter(shiz_page *pages, int count);

extern bool
shiz_exit(void);

extern int
shiz_get_page(void);

extern bool
shiz_set_page(int id);

extern int
shiz_handle(void);

extern shiz_field *
shiz_find_checkbox(shiz_page *page);

extern shiz_textbox_data *
shiz_find_textbox(shiz_page *page);

extern int
shiz_check_page(const shiz_page *page, void *param);

extern bool
shiz_refresh_field(shiz_page *page, int id);

extern bool
shiz_request_notify(int cookie);

#endif // SHARIZARD_H
