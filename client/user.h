#ifndef USER_H
#define USER_H

#include <iostream>

#include <QDataStream>

class User {
 public:
  User(QString name = "None", int point = 0);

  ~User();

  friend QDataStream& operator << (QDataStream &out, User const& user);


  enum GameStatus {Wait = 0, Go = 1};

  int get_status() const;

  void set_status(int status);

  void set_point(int point);

  int get_point() const;

  QString get_name() const;

private:
 QString name_;
 int status_;
 int point_;

};

inline QDataStream& operator <<(QDataStream &out, User const& user)
{
     out << user.name_;
     out << user.status_;
     out << user.point_;
     return out;
}


#endif // USER_H

