#ifndef _vt520_tinybuffer_h
#define _vt520_tinybuffer_h

namespace Tiny { // Tiny Tools Namespace
    template <class Type, unsigned Size> class Buffer {
    private:
        Type buffer_table[Size];
        unsigned insertPointer = 0;
        unsigned readPointer = 0;
        
    public:
        const unsigned capacity = Size - 1;
        Buffer() {}
        Buffer(const Type * buffer) {InsertString(buffer);}
        Buffer(Type array[], unsigned length) { InsertAll(array, length); } 

        unsigned Count() {
            unsigned count = insertPointer - readPointer;
            if (readPointer > insertPointer) count -= Size;
            return count;
        }

        unsigned Free() {
            return capacity - Count();
        }

        Type Read() {
            if (readPointer != insertPointer) { // empty condition
                Type result = buffer_table[readPointer++];
                if (Size == readPointer) readPointer -= Size;
                return result;
            }
            return Type();
        }

        unsigned ReadInto(Type buffer[], unsigned buffer_size) {
            unsigned items_read = 0;
            if (buffer_size > Count()) buffer_size = Count();
            while (buffer_size > items_read) {
                buffer[items_read++] = Read();
            }
            return items_read;
        }
        bool Insert(Type item) {
            unsigned free = capacity - Count();
            if (0 <  free) {
                buffer_table[insertPointer++] = item;
                if (Size == insertPointer) insertPointer -= Size;
                return true;
            }
            return false;
        }
        bool InsertString(const Type * buffer) {
            unsigned index = 0;
            Type _default = Type();
            while(buffer[index++] != _default) {
                if(!Insert(buffer[index])) break;
            }
        }
        bool InsertAll(Type buffer[], unsigned count) {
            unsigned free =  capacity - Count();
            if (count <= free) {
                bool result = true;
                for (unsigned index = 0; index < count; index++) {
                    result &= Insert(buffer[index]);
                }
                return result;
            }
            return false;
        }
    };
}
#endif