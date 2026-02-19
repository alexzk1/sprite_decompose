#ifndef SAVABLE_WIDGET_H
#define SAVABLE_WIDGET_H

#include <QObject>
#include <QPointer>
#include <QSettings>
#include <QWidget>

#include <atomic>
#include <map>
#include <utility>
namespace utility {

template <class T>
class SaveableWidget
{
  private:
    // we should use plain pointer as key, but it may be deleted, thats why hold QPointer to do real
    // access
    struct value_t
    {
        QPointer<QWidget> ptr;
        QByteArray value;
    };
    std::map<QWidget *, value_t> lastSett;
    const QString prefix;

    static inline std::atomic<bool> &getResetter()
    {
        static std::atomic<bool> need_reset(false);
        return need_reset;
    }

  protected:
    SaveableWidget() = default;
    SaveableWidget(QString prefix) :
        lastSett(),
        prefix(std::move(prefix))
    {
    }

    QString getSettingsGroupName(QWidget *widget) const
    {
        return prefix + widget->objectName();
    }

    void readSettings(QWidget *window)
    {
        if (window)
        {
            lastSett[window] = value_t{window, window->saveGeometry()};
            if (!getResetter())
            {
                QSettings settings;

                settings.beginGroup(getSettingsGroupName(window));
                QVariant value = settings.value("geometry");

                if (!value.isNull())
                    window->restoreGeometry(value.toByteArray());
                else
                {
                    // supporting old saves
                    value = settings.value("pos");
                    if (!value.isNull())
                    {
                        window->move(settings.value("pos").toPoint());
                        window->resize(settings.value("size").toSize());
                    }
                }
                recurseRead(settings, window);
                settings.endGroup();
            }
            getResetter() = false;
        }
    }

    void writeSettings(QWidget *window)
    {
        if (window)
        {
            QSettings settings;

            settings.beginGroup(getSettingsGroupName(window));
            settings.setValue("pos", window->pos());
            settings.setValue("size", window->size());
            settings.setValue("geometry", window->saveGeometry());

            recurseWrite(settings, window);
            settings.endGroup();
            settings.sync();
        }
    }

    virtual void recurseRead(QSettings &settings, QObject *object)
    {
        Q_UNUSED(settings)
        Q_UNUSED(object)
    }
    virtual void recurseWrite(QSettings &settings, QObject *object)
    {
        Q_UNUSED(settings)
        Q_UNUSED(object)
    }
    virtual ~SaveableWidget() = default;

  public:
    void resetSizePos()
    {
        for (const auto &p : lastSett)
        {
            if (p.second.ptr)
                p.second.ptr->restoreGeometry(p.second.value);
        }
    }

    static void resetUIOnRead()
    {
        getResetter() = true;
    }
};

} // namespace utility
#endif // SAVABLE_WIDGET_H
