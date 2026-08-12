#include <jni.h>

#define MAX_PAYLOAD_SIZE 1024

static __thread char tls_buf[MAX_PAYLOAD_SIZE];

int telemetry_java_tls_write_enter(const char *buf, int len) {
    asm volatile("" ::: "memory");
    return len;
}

int telemetry_java_tls_read_exit(const char *buf, int len) {
    asm volatile("" ::: "memory");
    return len;
}

JNIEXPORT void JNICALL Java_io_telemetryinc_agent_NativeBridge_tlsWriteEnter(
    JNIEnv *env, jclass cls, jbyteArray data, jint offset, jint length)
{
    jint n = length < MAX_PAYLOAD_SIZE ? length : MAX_PAYLOAD_SIZE;
    (*env)->GetByteArrayRegion(env, data, offset, n, (jbyte *)tls_buf);
    telemetry_java_tls_write_enter(tls_buf, length);
}

JNIEXPORT void JNICALL Java_io_telemetryinc_agent_NativeBridge_tlsReadExit(
    JNIEnv *env, jclass cls, jbyteArray data, jint offset, jint length)
{
    jint n = length < MAX_PAYLOAD_SIZE ? length : MAX_PAYLOAD_SIZE;
    (*env)->GetByteArrayRegion(env, data, offset, n, (jbyte *)tls_buf);
    telemetry_java_tls_read_exit(tls_buf, length);
}
