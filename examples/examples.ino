#include <Arduino.h>
#include <TinyBuffer.h>
Tiny::Buffer<char, 64> static_buffer = "this buffer stores";
char message[] = "a message";
void setup() {
    static_buffer.InsertString(message);
    while(static_buffer.Free() > 0) {
        static_buffer.Insert(1);
    }
    while(static_buffer.Count() > 0) {
        Serial.print(static_buffer.Read());
    }
}
void loop () {

}
