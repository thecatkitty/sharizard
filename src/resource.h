#ifndef RESOURCE_H
#define RESOURCE_H

#define SHIZ_WINRES(x) (0x7a53 + (x)) // little-endian 'Sz'

#define IDD_PROMPT SHIZ_WINRES(1)
#define IDD_VACAT  SHIZ_WINRES(2)

#define IDC_ALERT   SHIZ_WINRES(1)
#define IDC_BANG    SHIZ_WINRES(2)
#define IDC_EDITBOX SHIZ_WINRES(3)
#define IDC_CHECK   SHIZ_WINRES(4)
#define IDC_TEXT    SHIZ_WINRES(5)

#define IDB_HEADER SHIZ_WINRES(1)

#define IDS_CANCEL SHIZ_WINRES(1)
#define IDS_BACK   SHIZ_WINRES(2)
#define IDS_NEXT   SHIZ_WINRES(3)

#endif // RESOURCE_H
