/**
 * Unit Tests for GoalUndo class
**/

#include <gtest/gtest.h>
#include "GoalUndo.h"
 
class GoalUndoTest : public ::testing::Test
{
	protected:
		GoalUndoTest(){}
		virtual ~GoalUndoTest(){}
		virtual void SetUp(){}
		virtual void TearDown(){}
};

TEST(GoalUndoTest, sanityCheck)
{
	ASSERT_TRUE(true);
}


/* getOperation() testing */


TEST(GoalUndoTest, get_operation_SingleOperation)
{
	GoalUndo goal;
	goal.addOperation("Goal1","op1");
	ASSERT_EQ("op1",goal.getOperations());
}


TEST(GoalUndoTest, get_operation_listOfAllOperations)
{
	GoalUndo goal;
	goal.addOperation("Goal1","op1");
	goal.addOperation("op2");
	ASSERT_EQ("op1 op2",goal.getOperations());
}



TEST(GoalUndoTest, get_operation_EmptyGoal)
{
	GoalUndo goal;
	ASSERT_EQ("",goal.getOperations());
}


TEST(GoalUndoTest, get_operation_createGoal_addOperation)
{
	GoalUndo goal;
	goal.addOperation("op1");
	goal.addOperation("op2");
	ASSERT_EQ("op1 op2",goal.getOperations());
}

/* getGoal() unit testing*/

TEST(GoalUndoTest, get_Goal_CreateGoal)
{
	GoalUndo goal;
	goal.addOperation("op1");
	ASSERT_EQ("op1",goal.getGoal());
}

TEST(GoalUndoTest, get_Goal_mostRecentGoal)
{
	GoalUndo goal;
	goal.addOperation("goal1","op1");
	goal.addOperation("goal2","op2");
	goal.addOperation("goal3","op3");
	ASSERT_EQ("goal3",goal.getGoal());
}


TEST(GoalUndoTest, get_Goal_EmptyGoal)
{
	GoalUndo goal;
	ASSERT_EQ("",goal.getGoal());
}


/* addOperations() unit testing*/

TEST(GoalUndoTest, add_Operations_EmptyGoal)
{
	GoalUndo goal;
	goal.addOperation("","op1");
	ASSERT_EQ("",goal.getGoal());
}

TEST(GoalUndoTest, add_Operations_EmptyOperation)
{
	GoalUndo goal;
	goal.addOperation("goal1","");
	ASSERT_EQ("",goal.getGoal());
}

TEST(GoalUndoTest, add_Operations_EmptyGoalandOperation)
{
	GoalUndo goal;
	goal.addOperation("","");
	ASSERT_EQ("",goal.getGoal());
}

TEST(GoalUndoTest, add_Operations_GoalbutEmptyOperation)
{
	GoalUndo goal;
	goal.addOperation("goal1","op1");

	goal.addOperation("");
	ASSERT_EQ("op1",goal.getOperations());
}




/*undoOperation() unit testing */

TEST(GoalUndoTest, undo_Operation_mostRecentOperation)
{
	GoalUndo goal;
	goal.addOperation("goal1","op1");
	goal.addOperation("op2");
	goal.addOperation("op3");
	goal.undoOperation();
	ASSERT_EQ("op1 op2",goal.getOperations());
}

TEST(GoalUndoTest, undo_Operation_singleOperation)
{
	GoalUndo goal;
	goal.addOperation("goal1","op1");
	goal.undoOperation();
	ASSERT_EQ("",goal.getOperations());
}

TEST(GoalUndoTest, undo_Operation_singleOperation_removeGoal)
{
	GoalUndo goal;
	goal.addOperation("goal1","op1");
	goal.undoOperation();
	ASSERT_EQ("",goal.getGoal());
}

TEST(GoalUndoTest, undo_Operation_matchedOpName)
{
	GoalUndo goal;
	goal.addOperation("goal1","op1");
	goal.addOperation("op2");
	goal.addOperation("op3");

	goal.undoOperation("op2");
	ASSERT_EQ("op1 op3",goal.getOperations());
}

TEST(GoalUndoTest, undo_Operation_noMatchedOpName)
{
	GoalUndo goal;
	goal.addOperation("goal1","op1");
	goal.addOperation("op2");
	goal.addOperation("op3");

	goal.undoOperation("op4");
	ASSERT_EQ("op1 op2 op3",goal.getOperations());
}

TEST(GoalUndoTest, undo_Operation_multipleOpSameName)
{
	GoalUndo goal;
	goal.addOperation("goal1","op1");
	goal.addOperation("op2");
	goal.addOperation("op3");
	goal.addOperation("op4");
	goal.addOperation("op5");
	goal.addOperation("op2");
	goal.addOperation("op7");
	goal.addOperation("op8");

	goal.undoOperation("op2");
	ASSERT_EQ("op1 op2 op3 op4 op5 op7 op8",goal.getOperations());
}


TEST(GoalUndoTest, undo_Operation_emptyGoal)
{
	GoalUndo goal;
	goal.undoOperation();
	ASSERT_EQ("",goal.getOperations());
}

TEST(GoalUndoTest, undo_Operation_emptyGoal_getOp)
{
	GoalUndo goal;
	goal.undoOperation("op1");
	ASSERT_EQ("",goal.getOperations());
}

TEST(GoalUndoTest, undo_Operation_emptyGoal_withParameter)
{
	GoalUndo goal;
	goal.addOperation("goal1","op1");
	goal.undoOperation("op1");
	ASSERT_EQ("",goal.getGoal());
}



TEST(GoalUndoTest, undo_Operation_NoGoal)
{
	GoalUndo goal;
	goal.undoOperation();
	ASSERT_EQ("",goal.getGoal());
}

/* undoGoal() unit testing */ 

TEST(GoalUndoTest, undo_Goal)
{
	GoalUndo goal;
	goal.undoGoal();
	ASSERT_EQ("",goal.getGoal());
}


TEST(GoalUndoTest, undo_Goal_withOperations)
{
	GoalUndo goal;
	goal.addOperation("goal1","op1");
	goal.undoGoal();
	ASSERT_EQ("",goal.getGoal());
}


TEST(GoalUndoTest, undo_Goal_multipleGoal_withOperations)
{
	GoalUndo goal;
	goal.addOperation("goal1","op1");
	goal.addOperation("goal2","op2");
	goal.undoGoal();
	ASSERT_EQ("goal1",goal.getGoal());
}