/*
 * UICmdParser.h
 *
 *  Created on: Dec 22, 2016
 *      Author: sajjadmuscle
 */

#ifndef UICMDPARSER_H_
#define UICMDPARSER_H_

#include <QString>

namespace au {

    class UICmdParser {
    public:

        void parse(const QString &commands);
        virtual const QString &result() const;
        virtual void clearResult();

        virtual ~UICmdParser() {
        }

    private:
        //      virtual void do_set(const QString &variable, const QString &value) = 0;
        //      virtual void do_get(const QString &variable) = 0;
        virtual void do_mavros_state() = 0;
        virtual void do_take_off(const QString &value) = 0;
        virtual void do_guided_mode() = 0;
        virtual void do_arm() = 0;
        virtual void do_fill_wayPoint(const QString &commands) = 0;
        virtual void do_start_mission() = 0;
        virtual void do_land_mode() = 0;
        virtual void do_rtl_mode() = 0;

    protected:
        QString resultString;
        QString lastCommand;
    public:
        bool doWrite;
    };

} /* namespace au */

#endif /* UICMDPARSER_H_ */