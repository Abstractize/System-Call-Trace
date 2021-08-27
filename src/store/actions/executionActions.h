/**
 * @file executionActions.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../action-types/executionActionTypes.h"
/**
 * @brief 
 * 
 */
typedef struct ExecuteAction
{
    ExecutionMode type;
};
/**
 * @brief 
 * 
 */
typedef struct ExecuteInteractive
{
    ExecuteAction action = {INTERACTIVE};
};
/**
 * @brief 
 * 
 */
typedef struct ExecuteNonInteractive
{
    ExecuteAction action = {NONINTERACTIVE};
};