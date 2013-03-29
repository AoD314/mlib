/*M/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (c) 2012 Morozov Andrey (morozov.andrey.vmk@gmail.com)
//    All Rights Reserved.
//
//    Redistribution and use in source and binary forms, with or without
//    modification, are permitted provided that the following conditions
//    are met:
//        1. Redistributions of source code must retain the above copyright
//           notice, this list of conditions and the following disclaimer.
//        2. Redistributions in binary form must reproduce the above copyright
//           notice, this list of conditions and the following disclaimer in
//           the documentation and/or other materials provided with
//           the distribution.
//        3. The name of the author may not be used to endorse or promote
//           products derived from this software without specific prior
//           written permission.
//
//    THIS SOFTWARE IS PROVIDED BY "AS IS" AND ANY EXPRESS OR
//    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//    ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
//    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
//    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
//    IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//    THE POSSIBILITY OF SUCH DAMAGE.
//
//M*/

#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <mlib/ilogger.hpp>
#include <mlib/convert.hpp>

namespace mlib
{

    class Logger : public ILogger
    {
        private:
            std::string file_name;

        public:
            Logger(const std::string & filename);
            void log(std::string msg);
    };

}

#undef LOG_INF
#undef LOG_DBG
#undef LOG_ERR

#define LOG_INF(msg)  std::string("[INFO]  ") + std::string(msg)

#define LOG_DBG(msg) \
    std::string("[DEBUG][") \
    + std::string(__FILE__).erase(0, 1 + std::string(__FILE__).find_last_of("/\\"))\
    + std::string(":") + std::string(mlib::to_str(__LINE__)) \
    + std::string("]  ") + std::string(msg)

#define LOG_ERR(msg) \
    std::string("[ERROR][") \
    + std::string(__FILE__).erase(0, 1 + std::string(__FILE__).find_last_of("/\\"))\
    + std::string(":") + std::string(mlib::to_str(__LINE__)) \
    + std::string("]  ") + std::string(msg)

#endif

