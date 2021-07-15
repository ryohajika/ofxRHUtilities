//
//  RHUtils.h
//  POSIX OS ONLY!!!!! (since this part rely on <pthread>)
//  chuck in all the static functions and classes quite useful ;)
//
//  Created by Ryo Hajika on 2020/09/23.
//

#pragma once

#include "ofMain.h"
#include <pthread.h>

namespace ofxRHUtilities {

// https://qiita.com/luftfararen/items/e5bc5b72017d71c73226
struct StopWatch {
    StopWatch(){
        start();
    }
    void start(){
        pre_ = std::chrono::high_resolution_clock::now();
    }
    double lap(){ // in MS
        auto tmp = std::chrono::high_resolution_clock::now();
        auto dur = tmp - pre_;
        pre_ = tmp;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count() / 1000000.0;
    }
    
    std::chrono::high_resolution_clock::time_point pre_;
};

class SimpleCsvLogger {
public:
    SimpleCsvLogger(){
        
    }
    ~SimpleCsvLogger(){
        if(os.is_open()) os.close();
    }
    void start(std::vector<std::string> & header, std::string full_file_name){
        row_header = &header;
        if(os.is_open()) os.close();
        
        if(ofFilePath::isAbsolute(full_file_name)){
            ofLogNotice("CsvLogger::start", "FilePath looks fine: %s", full_file_name.c_str());
        }else{
            ofLogNotice("CsvLogger::start", "FilePath doesn't look fine so store it to data dir");
            full_file_name.insert(0, ofFilePath::getAbsolutePath("")+"/");
        }
        
        os.open(full_file_name);
        for(int i=0; i<row_header->size(); i++){
            os << row_header->at(i);
            if(i < row_header->size() - 1){
                os << ",";
            }else{
                os << "\n";
            }
        }
    }
    
//    // http://coliru.stacked-crooked.com/a/17de1d94c52f2156
//    template <typename Value, typename... Values>
//    std::string update(Value v, Values... vs){
//        std::ostringstream oss;
//        using expander = std::string[];
//        oss << v;
//        (void) expander{ 0, (oss << "," << vs, void(), "")... };
//        os << oss.str() << "\n";
//        return oss.str();
//    }
    template <typename T, typename A0>
    void update(const A0 & a0){
        os << a0 << "\n";
    }
    template <typename T, typename A0, typename A1>
    void update(const A0 & a0, const A1 & a1){
        os << a0 << "," << a1 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2>
    void update(const A0 & a0, const A1 & a1, const A2 & a2){
        os << a0 << "," << a1 << "," << a2 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8>
    void update(const A0  a0, const A1  a1, const A2  a2, const A3  a3, const A4  a4, const A5  a5,
                const A6  a6, const A7  a7, const A8  a8){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9, const A10 & a10){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9, const A10 & a10, const A11 & a11){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "," << a11 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9, const A10 & a10, const A11 & a11,
                const A12 & a12){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "," << a11 << "," << a12 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
              typename A13>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9, const A10 & a10, const A11 & a11,
                const A12 & a12, const A13 & a13){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "," << a11 << "," << a12
            << "," << a13 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
              typename A13, typename A14>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9, const A10 & a10, const A11 & a11,
                const A12 & a12, const A13 & a13, const A14 & a14){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "," << a11 << "," << a12
            << "," << a13 << "," << a14 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
              typename A13, typename A14, typename A15>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9, const A10 & a10, const A11 & a11,
                const A12 & a12, const A13 & a13, const A14 & a14, const A15 & a15){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "," << a11 << "," << a12
            << "," << a13 << "," << a14 << "," << a15 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
              typename A13, typename A14, typename A15, typename A16>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9, const A10 & a10, const A11 & a11,
                const A12 & a12, const A13 & a13, const A14 & a14, const A15 & a15, const A16 & a16){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "," << a11 << "," << a12
            << "," << a13 << "," << a14 << "," << a15 << "," << a16 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
              typename A13, typename A14, typename A15, typename A16, typename A17>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9, const A10 & a10, const A11 & a11,
                const A12 & a12, const A13 & a13, const A14 & a14, const A15 & a15, const A16 & a16, const A17 & a17){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "," << a11 << "," << a12
            << "," << a13 << "," << a14 << "," << a15 << "," << a16 << "," << a17 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
              typename A13, typename A14, typename A15, typename A16, typename A17, typename A18>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9, const A10 & a10, const A11 & a11,
                const A12 & a12, const A13 & a13, const A14 & a14, const A15 & a15, const A16 & a16, const A17 & a17,
                const A18 & a18){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "," << a11 << "," << a12
            << "," << a13 << "," << a14 << "," << a15 << "," << a16 << "," << a17 << "," << a18 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
              typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9, const A10 & a10, const A11 & a11,
                const A12 & a12, const A13 & a13, const A14 & a14, const A15 & a15, const A16 & a16, const A17 & a17,
                const A18 & a18, const A19 & a19){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "," << a11 << "," << a12
            << "," << a13 << "," << a14 << "," << a15 << "," << a16 << "," << a17 << "," << a18
            << "," << a19 << "\n";
    }
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
              typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19,
              typename A20>
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8, const A9 & a9, const A10 & a10, const A11 & a11,
                const A12 & a12, const A13 & a13, const A14 & a14, const A15 & a15, const A16 & a16, const A17 & a17,
                const A18 & a18, const A19 & a19, const A20 & a20){
        os << a0 << "," << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6
            << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "," << a11 << "," << a12
            << "," << a13 << "," << a14 << "," << a15 << "," << a16 << "," << a17 << "," << a18
            << "," << a19 << "," << a20 << "\n";
    }
    
    void stop(){
        os.close();
    }
    
private:
    std::ofstream os;
    std::vector<std::string> * row_header;
};

// followed https://www.bo-yang.net/2017/11/19/cpp-kill-detached-thread
// for thread management
typedef std::unordered_map<std::string, pthread_t> ThreadMap;

// usually there's no much difference between the keywords
// "class" and "typename", but there are some exception
// https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates
// https://stackoverflow.com/questions/22532512/how-to-bind-store-and-execute-a-stdfunction-object

class BackgroundThreadManager {
    private:
        ThreadMap tm_;
        bool _b_verbose;
        
    public:
        BackgroundThreadManager(){
            _b_verbose = true;
        }
        ~BackgroundThreadManager(){
            if(_b_verbose){
                ofLogNotice() << __PRETTY_FUNCTION__;
            }
            if(tm_.size()){
                if(_b_verbose){
                    ofLogNotice() << "ThreadMap has size of: "
                                  << tm_.size()
                                  << ", and will be cleaned";
                }
                for(auto &t : tm_){
                    pthread_cancel(t.second);
                    tm_.erase(t.first);
                }
            }
        }
        
        void setVerbose(bool val){
            _b_verbose = val;
        }
        bool getVerbose(){
            return _b_verbose;
        }
        
        template <typename R>
        std::thread fireRepeatingThread(const std::string &tname,
                                        long interval_ms,
                                        std::function<R()> & func){
            if(_b_verbose){
                ofLogNotice() << __PRETTY_FUNCTION__;
            }
            std::thread _thread = std::thread([=](){
                while(1){
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(interval_ms)
                        );
                    func();
                }
            });
            tm_[tname] = _thread.native_handle();
            _thread.detach();
            return _thread;
        }
        
        template <typename R>
        std::thread fireThreadWithMS(const std::string &tname,
                                     long delay_ms,
                                     std::function<R()> & func){
            if(_b_verbose){
                ofLogNotice() << __PRETTY_FUNCTION__;
            }
            std::thread _thread = std::thread([=](){
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
                func();
            });
            tm_[tname] = _thread.native_handle();
            _thread.detach();
            return _thread;
        }
        
        template <typename R>
        std::thread fireThread(const std::string &tname,
                               std::function<R()> & func){
            if(_b_verbose){
                ofLogNotice() << __PRETTY_FUNCTION__;
            }
            std::thread _thread = std::thread([=](){
                func();
            });
            tm_[tname] = _thread.native_handle();
            _thread.detach();
            return _thread;
        }
        
        void cancelThread(const std::string & tname){
            // just a utility function to stop the worker thread
            // in case if the study is suspended on the half way
            if(_b_verbose){
                ofLogNotice() << __PRETTY_FUNCTION__;
            }
            ThreadMap::const_iterator it = tm_.find(tname);
            if(it != tm_.end()){
                if(_b_verbose){
                    ofLogNotice() << "Thread \"" << tname << "\" found and is gonna be cancelled";
                }
                pthread_cancel(it->second);
                tm_.erase(tname);
            }
        }
};

//const void cancelBackgroundThread(ThreadMap & tm, const std::string & tname){
//    // just a utility function to stop the worker thread
//	// in case if the study is suspended on the half way
//    ThreadMap::const_iterator it = tm.find(tname);
//    if(it != tm.end()){
//        pthread_cancel(it->second);
//        tm.erase(tname);
//    }
//}
//
//template <typename R>
//const std::shared_ptr<std::thread>
//fireBackgroundThread(ThreadMap & tm,
//                     const std::string & tname,
//                     const long delay_time_ms,
//                     std::function<R()> & func){
//    std::shared_ptr<std::thread> _thread = std::make_shared<std::thread>([=](){
//        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time_ms));
//        func();
//    });
//    tm[tname] = _thread->native_handle();
//    _thread->detach();
//    return _thread;
//}
//template <typename R, class... Args>
//const std::shared_ptr<std::thread> fireBackgroundThread(ThreadMap & tm,
//                                                        const std::string & tname,
//                                                        const long delay_time_ms,
//                                                        std::function<R(Args...)> func){
//    std::shared_ptr<std::thread> _thread = std::make_shared<std::thread>([=](){
//        std::this_thread::sleep_for(
//            std::chrono::milliseconds(delay_time_ms));
//        func();
//    });
//    tm[tname] = _thread->native_handle();
//    _thread->detach();
//    return _thread;
//}

// https://stackoverflow.com/questions/9094132/c-stdtransform-vector-of-pairs-first-to-new-vector
template <typename T1, typename T2>
const void vector_of_pairs_first_to_vector(std::vector<std::pair<T1, T2>> *src,
                                           std::vector<T1> *dst){
    std::transform(src->begin(),
                   src->end(),
                   std::back_inserter(dst),
                   [](const std::pair<T1, T2>&p){
                       return p.first;
                   });
}

template <typename T1, typename T2>
const void vector_of_pairs_second_to_vector(std::vector<std::pair<T1, T2>> *src,
                                            std::vector<T2> *dst){
    std::transform(src->begin(),
                   src->end(),
                   std::back_inserter(dst),
                   [](const std::pair<T1, T2>&p){
                       return p.second;
                   });
}

inline ofJson readJsonFromString(std::string & line){
    if(line.size()){
        ofJson _j;
        _j = operator""_json(line.c_str(), line.size());
        return _j;
    }else{
        return nullptr;
    }
}

inline long long getUnixTimeInMS(){
    return (long long) std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                       ).count();
}

}; // namespace ofxRHUtilities
