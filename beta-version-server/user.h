#ifndef USER_H
#define USER_H

#include <QDataStream>
#include <iostream>

class User {
 public:
  User(QString name = "None", int point = -1);
  ~User();

  friend QDataStream& operator>>(QDataStream &in, User & user);
  friend std::ostream& operator<<(std::ostream &out, User const & user);
  int get_game() const;
  void set_game(int game);
  void set_point(int point);
  int get_point() const;
  QString get_name() const;

private:
 QString name_;
 int point_;
 int game_;
};

inline QDataStream& operator >>(QDataStream &in, User & user) {
     in >> user.name_;
     in >> user.point_;
     in >> user.game_;
     return in;
}

inline std::ostream& operator<<(std::ostream &out, User const & user) {
     out << user.name_.toStdString();
     out << user.point_;
     out << user.game_;
     return out;
}

#endif // USER_H

