#include<iostream>

class String{
    private:
        uint32_t len;
        char *data;
    
    public:
        String() : len(0), data(nullptr){} //default constructor

        String(const char *str){ //parameterize constructor
            len = strlen(str);
            data = new char[len+1];
            strcpy(data, str);
        }

        String(const String& str){ //copy constructor
            if(this != &str){
                len = str.len;
                data = new char[len+1];
                strcpy(data, str.data);
            }
        }

        String& operator=(const String& str){ //copy assignment constructor
            if(this != &str){
                delete data;
                len = str.len;
                data = new char[len+1];
                strcpy(data, str.data);
            }
            return *this;
        }


        String(String&& str) noexcept{ //move constructor
            data = str.data;
            len = str.len;

            str.data = nullptr;
            str.len = 0;
        }

        String& operator=(String&& str){ //move assignment constructor
            delete data;

            data = str.data;
            len = str.len;

            str.data = nullptr;
            str.len = 0;

            return *this;
        }

        uint32_t length() const{
            return len;
        }

        String operator+(const String& str){
            uint32_t newLength = len + str.len;
            char* newStrData = new char[newLength + 1];
            strcpy(newStrData, data);
            strcat(newStrData, str.data);

            String newStr(newStrData);
            delete[] newStrData;

            return newStr;
        }

        bool operator==(const String& str){
            return strcmp(data, str.data) == 0;
        }

        char& operator[](uint32_t index){
            return data[index];
        }

        friend std::ostream& operator<<(std::ostream& out, const String& str){
            out << str.data;
            return out;
        }

        friend std::istream& operator>>(std::istream& in, String& str){
            char buffer[100000];
            in >> buffer;

            str = String(buffer);
            return in;
        }

        ~String(){
            delete data;
            data = nullptr;
            len = 0;
        }
};


int main(){

    String s1("Hello");
    String s2("World");
    String s3 = s1 + " " + s2;
    std::cout << "Concatenated: " << s3 << std::endl;

    String s4;
    std::cout << "Enter a string: ";
    std::cin >> s4;
    std::cout << "You entered: " << s4 << std::endl;

    // Move semantics demo
    String moved = std::move(s1);
    std::cout << "Moved string: " << moved << std::endl;
    // std::cout << "Now See s1: " << s1 << std::endl; // This is now null

    return 0;
}
