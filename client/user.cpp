# include "user.h"


  User::User(QString name, int point)
      : name_(name), point_(point), status_(0) {}

  User::~User() {}

  int User::get_status() const
  {
     return status_;
  }

  void User::set_status(int status) {
     status_ = status;
  }

  void User::set_point(int point) {
     point_ = point;
  }

  int User::get_point() const
  {
     return point_;
  }
  QString User::get_name() const
  {
       return name_;
  }
