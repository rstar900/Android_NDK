#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_hello_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hi from C++!";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_hello_MainActivity_process(JNIEnv *env, jobject mainActivityInstance) {

    // get the class instance and method id for "stringFromJava()" method
    const jclass mainActivityClass = env->GetObjectClass(mainActivityInstance);
    const jmethodID methodID = env->GetMethodID(mainActivityClass, "stringFromJava", "()Ljava/lang/String;");

    // check if methodID resolution was successful
    if (methodID == nullptr) {
        // return empty string in this case
        return env->NewStringUTF("");
    }

    // now call the method and get the string as jstring
    const jstring result = (jstring) env->CallObjectMethod(mainActivityInstance, methodID); // it would have been jobject by default
    // convert into std::string
    const std::string java_msg = env->GetStringUTFChars(result, JNI_FALSE);
    // append our message "C++ received from Java: "
    const std::string cpp_msg = "C++ received from Java: " + java_msg;
    // send back to app (java)
    return env->NewStringUTF(cpp_msg.c_str());
}