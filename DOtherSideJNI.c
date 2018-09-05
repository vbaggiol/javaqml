#include "DOtherSideJNI.h"

#include <DOtherSide/DOtherSide.h>

void Java_DOtherSideJNI_qapplication_1create(JNIEnv *env, jclass t)
{
    dos_qapplication_create();
}

void Java_DOtherSideJNI_qapplication_1exec(JNIEnv *env, jclass t)
{
    dos_qapplication_exec();
}

void Java_DOtherSideJNI_qapplication_1quit(JNIEnv *env, jclass t)
{
    dos_qapplication_quit();
}

void Java_DOtherSideJNI_qapplication_1delete(JNIEnv *env, jclass t)
{
    dos_qapplication_delete();
}
