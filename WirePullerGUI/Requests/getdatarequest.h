#ifndef GETDATAREQUEST_H
#define GETDATAREQUEST_H
#include "request.h"

class GetDataRequest : public Request {
 public:
  virtual QByteArray data() const override;
};

#endif // GETDATAREQUEST_H
