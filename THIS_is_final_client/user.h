#ifndef USER_H
#define USER_H

#include <iostream>

#include <QDataStream>

#include <QTime>

class User {
 public:
  User(QString name = "None", int point = -1);

  ~User();

  friend QDataStream& operator << (QDataStream &out, User const& user);

  friend QDataStream& operator>>(QDataStream &in, User & user);

  void set_point(int point);

  int get_point() const;

  void set_game(int game);

  int get_game() const;

  QString get_name() const;


private:
 QString name_;
 int point_;
 int game_;

};

inline QDataStream& operator <<(QDataStream &out, User const& user)
{
     out << user.name_;
     out << user.point_;
     out << user.game_;
     return out;
}

inline QDataStream& operator >>(QDataStream &in, User & user)
{
     in >> user.name_;
     in >> user.point_;
     in << user.game_;
     return in;
}

#endif // USER_H

