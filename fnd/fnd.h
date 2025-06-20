#ifndef _FND_LIB_H_
#define _FND_LIB_H_

#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)

typedef struct FNDWriteDataForm_tag {
    char DataNumeric[FND_DATA_BUFF_LEN];
    char DataDot[FND_DATA_BUFF_LEN];
    char DataValid[FND_DATA_BUFF_LEN];
} stFndWriteForm, *pStFndWriteForm;

int fndDisp(int num, int dotflag);
int fndDisp_Time(void);

#endif
