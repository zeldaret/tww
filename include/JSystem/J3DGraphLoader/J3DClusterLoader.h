#ifndef J3DCLUSTERLOADER_H
#define J3DCLUSTERLOADER_H

class J3DClusterBlock;

struct J3DClusterLoaderDataBase {
    static void* load(const void*);
};

class J3DClusterLoader {
public:
    virtual void* load(const void*) = 0;
    virtual ~J3DClusterLoader() {}
};

class J3DClusterLoader_v15 : public J3DClusterLoader {
public:
    J3DClusterLoader_v15();
    ~J3DClusterLoader_v15();
    void* load(const void*);
    void readCluster(const J3DClusterBlock*);
};

#endif /* J3DCLUSTERLOADER_H */
