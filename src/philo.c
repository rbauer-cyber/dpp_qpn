/*$file${.::philo.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: dpp.qm
* File:  ${.::philo.c}
*
* This code has been generated by QM 5.2.2 <www.state-machine.com/qm>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* SPDX-License-Identifier: GPL-3.0-or-later
*
* This generated code is open source software: you can redistribute it under
* the terms of the GNU General Public License as published by the Free
* Software Foundation.
*
* This code is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* NOTE:
* Alternatively, this generated code may be distributed under the terms
* of Quantum Leaps commercial licenses, which expressly supersede the GNU
* General Public License and are specifically designed for licensees
* interested in retaining the proprietary status of their code.
*
* Contact information:
* <www.state-machine.com/licensing>
* <info@state-machine.com>
*/
/*$endhead${.::philo.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#include "qpn.h"      // QP-nano framework
#include "philo.h"
#include "table.h"
#include "bsp.h"

//============================================================================
// define all AO classes...

Philo AO_Philo[N_PHILO];

/*$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/* Check for the minimum required QP version */
#if (QP_VERSION < 690U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpn version 6.9.0 or higher required
#endif
/*$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*$define${AOs::Philo} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${AOs::Philo} ............................................................*/

/*${AOs::Philo::SM} ........................................................*/
QState Philo_initial(Philo * const me) {
    /*${AOs::Philo::SM::initial} */
    DEBUG_ARGS("Philospher %d starting", me->m_id);
    return Q_TRAN(&Philo_thinking);
}

/*${AOs::Philo::SM::thinking} ..............................................*/
QState Philo_thinking(Philo * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*${AOs::Philo::SM::thinking} */
        case Q_ENTRY_SIG: {
            DEBUG_ARGS("Philospher %d thinking", me->m_id);
            QActive_armX(&me->super, 0U, THINK_TIME, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::Philo::SM::thinking} */
        case Q_EXIT_SIG: {
            QActive_disarmX(&me->super, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::Philo::SM::thinking::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            status_ = Q_TRAN(&Philo_hungry);
            break;
        }
        /*${AOs::Philo::SM::thinking::EAT, DONE} */
        case EAT_SIG: /* intentionally fall through */
        case DONE_SIG: {
            Q_ERROR(); /* these events should never arrive in this state */
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}

/*${AOs::Philo::SM::hungry} ................................................*/
QState Philo_hungry(Philo * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*${AOs::Philo::SM::hungry} */
        case Q_ENTRY_SIG: {
            DEBUG_ARGS("Philospher %d hungry", me->m_id);
            QACTIVE_POST(&AO_Table, HUNGRY_SIG, me->super.prio);
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::Philo::SM::hungry::EAT} */
        case EAT_SIG: {
            status_ = Q_TRAN(&Philo_eating);
            break;
        }
        /*${AOs::Philo::SM::hungry::DONE} */
        case DONE_SIG: {
            Q_ERROR(); /* this event should never arrive in this state */
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}

/*${AOs::Philo::SM::eating} ................................................*/
QState Philo_eating(Philo * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*${AOs::Philo::SM::eating} */
        case Q_ENTRY_SIG: {
            DEBUG_ARGS("Philospher %d eating", me->m_id);
            QActive_armX(&me->super, 0U, EAT_TIME, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::Philo::SM::eating} */
        case Q_EXIT_SIG: {
            QActive_disarmX(&me->super, 0U);
            QACTIVE_POST(QF_ACTIVE_CAST(&AO_Table), DONE_SIG, me->super.prio);
            status_ = Q_HANDLED();
            break;
        }
        /*${AOs::Philo::SM::eating::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            status_ = Q_TRAN(&Philo_thinking);
            break;
        }
        /*${AOs::Philo::SM::eating::EAT, DONE} */
        case EAT_SIG: /* intentionally fall through */
        case DONE_SIG: {
            Q_ERROR(); /* these events should never arrive in this state */
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*$enddef${AOs::Philo} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

