#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>
#include <QMetaType>

/** This class exports enums needed on the scripting side

  This is a placeholder for those enums that are in QtCreator (hence outside our control),
  and which we do not have Q_ENUMS registered fo them.
*/
class Enums :public QObject {
    Q_OBJECT
public:
    /** copied from ::TextEditor::ITextEditor::PositionOperation */
    enum PositionOperation {
        Current = 1,
        EndOfLine = 2,
        StartOfLine = 3,
        Anchor = 4,
        EndOfDoc = 5
    };
    Q_ENUMS(PositionOperation)
};

Q_DECLARE_METATYPE(Enums::PositionOperation)

#endif // ENUMS_H
