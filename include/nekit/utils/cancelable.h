// MIT License

// Copyright (c) 2017 Zhuhao Wang

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <memory>

#include <boost/noncopyable.hpp>

namespace nekit {
namespace utils {
class Cancelable {
 public:
  Cancelable();

  Cancelable(const Cancelable& cancelable);
  Cancelable& operator=(const Cancelable& cancelable);

  Cancelable(Cancelable&& cancelable);
  Cancelable& operator=(Cancelable&& cancelable);

  ~Cancelable();

  void Cancel();
  bool canceled() const;

 private:
  std::shared_ptr<bool> canceled_;
};

class LifeTime : private boost::noncopyable {
 public:
  LifeTime()
      : life_time_cancelable_{},
        life_time_cancelable_pointer_{
            std::make_shared<Cancelable>(life_time_cancelable_)} {}

  const Cancelable& life_time_cancelable() const {
    return life_time_cancelable_;
  }

  std::shared_ptr<Cancelable> life_time_cancelable_pointer() const {
    return life_time_cancelable_pointer_;
  }

 private:
  Cancelable life_time_cancelable_;
  std::shared_ptr<Cancelable> life_time_cancelable_pointer_;
};
}  // namespace utils
}  // namespace nekit