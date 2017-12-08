# include "user.h"


  User::User(QString name, int point)
      : name_(name), point_(point), game_(0) {}

  User::~User() {}

  int User::get_game() const
  {
     return game_;
  }

  void User::set_game(int game) {
     game_ = game;
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
