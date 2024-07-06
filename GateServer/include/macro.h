#ifndef _UCHAT_COMMON_MACRO_H_
#define _UCHAT_COMMON_MACRO_H_

#define UNCOPYABLE(class_name)                                                 \
  class_name(class_name const &) = delete;                                     \
  class_name(class_name &&) = delete;                                          \
  class_name &operator=(class_name const &) = delete;                           \
  class_name &operator=(class_name &&) = delete

#endif 