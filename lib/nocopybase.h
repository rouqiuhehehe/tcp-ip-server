//
// Created by Administrator on 2023/2/14.
//

#ifndef TEST_LIB_NOCOPYBASE_H_
#define TEST_LIB_NOCOPYBASE_H_
class NoCopyBase
{
protected:
    NoCopyBase () = default;
    NoCopyBase (const NoCopyBase &) = delete;
    NoCopyBase operator= (const NoCopyBase &) = delete;
};
#endif //TEST_LIB_NOCOPYBASE_H_
