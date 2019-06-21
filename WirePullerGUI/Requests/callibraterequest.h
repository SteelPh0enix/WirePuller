#ifndef CALLIBRATEREQUEST_H
#define CALLIBRATEREQUEST_H
#include "request.h"

class CallibrateRequest : public Request {
 public:
  virtual QByteArray data() const override;
};

#endif // CALLIBRATEREQUEST_H
