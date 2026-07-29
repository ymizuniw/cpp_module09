# include "InputFile.hpp"

InputFile::InputFile(): CSVParser() {
    
}

InputFile::InputFile(std::string file_name): CSVParser(file_name, '|', false){

}

InputFile::InputFile(const InputFile &other){
    if (this==&other) 
        return;
    record_=other.record_;
}

InputFile &InputFile::operator=(const InputFile &other){
    if (this==&other) 
        return(*this);
    record_=other.record_;
    file_name_=other.file_name_;
    return (*this);
}

InputFile::~InputFile(){
}

void InputFile::openFile(){
    file_stream_.open(file_name_, std::ios_base::in);
    file_stream_.exceptions(std::ios_base::badbit);
}


void InputFile::parseFile(){

}

void InputFile::sortRecord(){

} 

std::multimap<Date,float> getRecord(){

}
