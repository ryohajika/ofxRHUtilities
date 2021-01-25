//
//  UtilityThings.h
//
//  Created by Ryo Hajika on 2020/09/23.
//

#pragma once

#include <chrono>
#include <functional>
#include <future>
#include <utility>
#include <type_traits>
#include <vector>
#include <map>
#include <string>
#include <fstream>

#include "ofLog.h"
#include "ofFileUtils.h"

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
    void update(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4, const A5 & a5,
                const A6 & a6, const A7 & a7, const A8 & a8){
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


//namespace detail {
//    template <class T>
//    struct is_reference_wrapper : std::false_type {};
//    template <class U>
//    struct is_reference_wrapper<std::reference_wrapper<U>> : std::true_type {};
//
//    template<class T>
//    struct invoke_impl {
//        template<class F, class... Args>
//        static auto call(F&& f, Args&&... args)
//        -> decltype(std::forward<F>(f)(std::forward<Args>(args)...));
//    };
//
//    template<class B, class MT>
//    struct invoke_impl<MT B::*> {
//        template<class T, class Td = typename std::decay<T>::type,
//        class = typename std::enable_if<std::is_base_of<B, Td>::value>::type
//        >
//        static auto get(T&& t) -> T&&;
//
//        template<class T, class Td = typename std::decay<T>::type,
//        class = typename std::enable_if<is_reference_wrapper<Td>::value>::type
//        >
//        static auto get(T&& t) -> decltype(t.get());
//
//        template<class T, class Td = typename std::decay<T>::type,
//        class = typename std::enable_if<!std::is_base_of<B, Td>::value>::type,
//        class = typename std::enable_if<!is_reference_wrapper<Td>::value>::type
//        >
//        static auto get(T&& t) -> decltype(*std::forward<T>(t));
//
//        template<class T, class... Args, class MT1,
//        class = typename std::enable_if<std::is_function<MT1>::value>::type
//        >
//        static auto call(MT1 B::*pmf, T&& t, Args&&... args)
//        -> decltype((invoke_impl::get(std::forward<T>(t)).*pmf)(std::forward<Args>(args)...));
//
//        template<class T>
//        static auto call(MT B::*pmd, T&& t)
//        -> decltype(invoke_impl::get(std::forward<T>(t)).*pmd);
//    };
//
//    template<class F, class... Args, class Fd = typename std::decay<F>::type>
//    auto INVOKE(F&& f, Args&&... args)
//    -> decltype(invoke_impl<Fd>::call(std::forward<F>(f), std::forward<Args>(args)...));
//
//} // namespace detail
//
//template <class callable, class... arguments>
//void SimpleTimerCallbacker(unsigned after_ms, bool async, callable&& f, arguments&&... args){
//    //using a = std::result_of<callable(arguments...)>::type;
//    using a = decltype(std::result_of<std::declval<callable>(f(args)...)>);
//    std::function<typename a> task(std::bind(std::forward<callable>(f),
//                                             std::forward<arguments>(args)...));
//    if (async){
//        std::thread([after_ms, task]() {
//            std::this_thread::sleep_for(std::chrono::milliseconds(after_ms));
//            task();
//        }).detach();
//    }else{
//        std::this_thread::sleep_for(std::chrono::milliseconds(after_ms));
//        task();
//    }
//}

}; // namespace ofxRHUtilities
