#ifndef PATHSTACK_H
#define PATHSTACK_H

#include <QDebug>
#include <QDir>
#include <QObject>
#include <QString>
#include <stack>
#include <vector>

template <typename Type>
class PathStack_t {
 public:
  inline void push(const Type& value) { _stack.push_back(value); }
  Type pop() {
    Type temp = _stack.back();
    _stack.pop_back();
    return temp;
  }
  inline size_t size() const { return _stack.size(); }
  inline const Type& operator[](size_t index) const { return _stack[index]; }
  inline const Type& at(size_t index) const { return _stack[index]; }

 private:
  std::vector<Type> _stack;
};

class PathStack : public QObject {
  Q_OBJECT
 public:
  explicit PathStack(QObject* parent = nullptr);

  size_t currentIndex() const;
  QString currentPath() const;
  QString goNextPath();
  QString goBackPath();
  void setNewFullPath(const QString& fullPath);
  void pushSubPath(const QString& subPath);

 private:
  void setCurrentIndex(size_t currentIndex);
  void incrementCurrentIndex();
  void decrementCurrentIndex();
  void resetCurrentIndex() { setCurrentIndex(0); }
  PathStack_t<QString> _pathStack;
  size_t _currentIndex;
};

#endif  // PATHSTACK_H
