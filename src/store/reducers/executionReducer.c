#include "../action-types/executionActionTypes.h"
#include "../actions/executionActions.h"
#include "../states/executionState.h"
#include "../../infrastructure/interactive/executeInteractive.h"
#include "../../infrastructure/noninteractive/executeNonInteractive.h"

Execution ExecuteReducer(Execution state, ExecuteAction action)
{
    switch (action.type)
    {
    case INTERACTIVE:
        Execution newState = {
            ExecuteInteractive
        };
        return newState;
    case NONINTERACTIVE:
        Execution newState = {
            ExecuteNonInteractive
        };
        return newState;
    default:
        return state;
    }
}