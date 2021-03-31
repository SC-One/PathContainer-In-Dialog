#include "PathStack.h"

PathStack::PathStack(QObject *parent)
    : QObject(parent),
      _currentIndex(0)

{}

size_t PathStack::currentIndex() const { return _currentIndex; }

void PathStack::setCurrentIndex(size_t currentIndex) {
  if (currentIndex < _pathStack.size()) _currentIndex = currentIndex;
}

void PathStack::incrementCurrentIndex() { setCurrentIndex(currentIndex() + 1); }

void PathStack::decrementCurrentIndex() { setCurrentIndex(currentIndex() - 1); }

void PathStack::pushSubPath(const QString &subPath) {
  QRegExp rx("/");  // RegEx for ' ' or ',' or '.' or ':' or '\t'
  QStringList paths = subPath.split(rx);
  for (int i = 0; i < paths.size(); ++i) {
    qDebug() << "====>" << paths[i];
    if (!paths[i].isEmpty()) {
      _pathStack.push(paths[i]);
      incrementCurrentIndex();
    }
  }
}

QString PathStack::currentPath() const {
  QString ret;
  for (size_t i = 0; i < _pathStack.size(); ++i) {
    ret.append("/" + _pathStack[i]);
  }
  return ret;
}

QString PathStack::goNextPath() {
  incrementCurrentIndex();
  return currentPath();
}

QString PathStack::goBackPath() {
  decrementCurrentIndex();
  return currentPath();
}

void PathStack::setNewFullPath(const QString &fullPath) {
  auto currentPath = this->currentPath();
  if (fullPath.indexOf(currentPath) == 0) {
    pushSubPath(fullPath.mid(currentPath.size()));
  } else {
    resetCurrentIndex();
    pushSubPath(fullPath.mid(currentPath.size()));
  }
}
