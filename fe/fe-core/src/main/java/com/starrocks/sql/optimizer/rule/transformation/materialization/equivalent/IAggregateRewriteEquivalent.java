// Copyright 2021-present StarRocks, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package com.starrocks.sql.optimizer.rule.transformation.materialization.equivalent;

import com.starrocks.sql.optimizer.operator.scalar.CallOperator;
import com.starrocks.sql.optimizer.operator.scalar.ColumnRefOperator;
import com.starrocks.sql.optimizer.operator.scalar.ScalarOperator;

public abstract class IAggregateRewriteEquivalent implements IRewriteEquivalent {
    public RewriteEquivalentType getRewriteEquivalentType() {
        return RewriteEquivalentType.AGGREGATE;
    }

    /**
     * Rewrite the aggregate function with rollup.
     * @param shuttleContext: the context of equivalent shuttle
     * @param aggFunc: the aggregate function to rewrite
     * @param replace: the column ref to replace
     * @return: the rewritten aggregate function
     */
    abstract ScalarOperator rewriteRollupAggregateFunc(EquivalentShuttleContext shuttleContext,
                                                       CallOperator aggFunc,
                                                       ColumnRefOperator replace);

    /**
     * Rewrite the aggregate function with no rollup.
     * @param shuttleContext: the context of equivalent shuttle
     * @param aggFunc: the aggregate function to rewrite
     * @param replace: the column ref to replace
     * @return: the rewritten aggregate function
     */
    abstract ScalarOperator rewriteAggregateFunc(EquivalentShuttleContext shuttleContext,
                                                 CallOperator aggFunc,
                                                 ColumnRefOperator replace);

    /**
     * Rewrite the aggregate function after check.
     * @param shuttleContext: the context of equivalent shuttle
     * @param aggFunc: the aggregate function to rewrite
     * @param replace: the column ref to replace
     * @param isRollup: whether the rewrite is for rollup
     * @return: the rewritten aggregate function
     */
    public ScalarOperator rewriteImpl(EquivalentShuttleContext shuttleContext,
                                      CallOperator aggFunc,
                                      ColumnRefOperator replace,
                                      boolean isRollup) {
        if (isRollup) {
            return rewriteRollupAggregateFunc(shuttleContext, aggFunc, replace);
        } else {
            return rewriteAggregateFunc(shuttleContext, aggFunc, replace);
        }
    }
}