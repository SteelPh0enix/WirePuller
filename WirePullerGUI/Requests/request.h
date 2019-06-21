#ifndef REQUEST_H
#define REQUEST_H

#include <QByteArray>

class Request {
 public:
  virtual ~Request() = default;
  virtual QByteArray data() const = 0;
};

#endif // REQUEST_H
