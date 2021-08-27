#include "./actions/executionActions.h"
#include "./reducers/executionReducer.h"
#include "./states/executionState.h"

struct Execution dispatch(struct ExecuteAction action)
{
    struct Execution state = ExecuteReducer(action);
    return state;
}