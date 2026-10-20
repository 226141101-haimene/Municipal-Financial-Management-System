#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 100
#define TEXT_LEN   100

typedef struct {
    int    id;
    char   name[TEXT_LEN];
    char   type[TEXT_LEN];
    double purchaseValue;
    char   department[TEXT_LEN];
    char   condition[TEXT_LEN];
} Asset;

void displayAssetMenu(void);
int  assetCount(void);

#endif
