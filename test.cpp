#include "gtest/gtest.h"
#include "composite.h"
#include "command.h"
#include "menu.h"
	
	
TEST(OpCommand, testing) {
	OpCommand* op1 = new OpCommand(3.14);
	OpCommand* op2 = new OpCommand(-6.11);
	OpCommand* op3 = new OpCommand(0);
	OpCommand* op4 = new OpCommand(654.48); 
	
	EXPECT_EQ(3.14, op1->execute()); 
	EXPECT_EQ(-6.11, op2->execute());
	EXPECT_EQ(0, op3->execute());
	EXPECT_EQ(654.48, op4->execute());
}
	
TEST(AddCommand, testing) {
	AddCommand* add1 = new AddCommand(new OpCommand(3.14), -0.14);
	AddCommand* add2 = new AddCommand(new OpCommand(5), 7);
	AddCommand* add3 = new AddCommand(new OpCommand(-11.9), -5);
	AddCommand* add4 = new AddCommand(new OpCommand(654.48), 45.52); 
	
	EXPECT_EQ(3.0, add1->execute()); 
	EXPECT_EQ(12.0, add2->execute());
	EXPECT_EQ(-16.9, add3->execute());
	EXPECT_EQ(700.0, add4->execute());
}
	
TEST(SubCommand, testing) {
	SubCommand* sub1 = new SubCommand(new OpCommand(3.145), -0.14);
	SubCommand* sub2 = new SubCommand(new OpCommand(5), 7);
	SubCommand* sub3 = new SubCommand(new OpCommand(-11.9), -5);
	SubCommand* sub4 = new SubCommand(new OpCommand(654.48), 45.52); 
	
	EXPECT_EQ(3.285, sub1->execute()); 
	EXPECT_EQ(-2.0, sub2->execute());
	EXPECT_EQ(-6.9, sub3->execute());
	EXPECT_EQ(608.96, sub4->execute());
}
	
TEST(MultCommand, testing) {
	MultCommand* mult1 = new MultCommand(new OpCommand(3.145), -0.14);
	MultCommand* mult2 = new MultCommand(new OpCommand(5), 7);
	MultCommand* mult3 = new MultCommand(new OpCommand(-11.9), -5);
	MultCommand* mult4 = new MultCommand(new OpCommand(5.2), 6.8); 
	
	EXPECT_EQ(-0.4403, mult1->execute()); 
	EXPECT_EQ(35.0, mult2->execute());
	EXPECT_EQ(59.5, mult3->execute());
	EXPECT_EQ(35.36, mult4->execute());
}
	
TEST(SqrCommand, testing) {
	SqrCommand* sqr1 = new SqrCommand(new OpCommand(3.14));
	SqrCommand* sqr2 = new SqrCommand(new OpCommand(5));
	SqrCommand* sqr3 = new SqrCommand(new OpCommand(-11.9));
	SqrCommand* sqr4 = new SqrCommand(new OpCommand(6.3)); 
	
	EXPECT_EQ(9.8596, sqr1->execute()); 
	EXPECT_EQ(25.0, sqr2->execute());
	EXPECT_EQ(141.61, sqr3->execute());
	EXPECT_EQ(39.69, sqr4->execute());
}
	
TEST(Menu, testing) {
	Menu* menu = new Menu();
	
	EXPECT_EQ(false, menu->initialized()); 
	
	menu->add_command(new OpCommand(7.6));
	
	EXPECT_EQ(true, menu->initialized());
	EXPECT_EQ(7.6, menu->get_command()->execute());
	
	menu->undo(); 
	menu->redo();
	
	EXPECT_EQ(7.6, menu->get_command()->execute());
	
	menu->add_command(new SqrCommand(menu->get_command()));
	
	EXPECT_EQ(57.76, menu->get_command()->execute());
	
	menu->add_command(new SubCommand(menu->get_command(), 47.76));
	
	EXPECT_EQ(10.0, menu->get_command()->execute());
	
	menu->undo();
	
	EXPECT_EQ(57.76, menu->get_command()->execute());
	
	menu->redo();
	
	EXPECT_EQ(10.0, menu->get_command()->execute());
	
	menu->add_command(new AddCommand(menu->get_command(), -5.4));
	
	EXPECT_EQ(4.6, menu->get_command()->execute());
	
	menu->add_command(new MultCommand(menu->get_command(), 4.2));
	
	EXPECT_EQ(19.32, menu->get_command()->execute());
	
	menu->redo();
	
	EXPECT_EQ(19.32, menu->get_command()->execute());
	
	menu->undo();
	
	EXPECT_EQ(4.6, menu->get_command()->execute());
	
	testing::internal::CaptureStdout();
	menu->execute(); 
	string output = testing::internal::GetCapturedStdout();
	
	EXPECT_EQ(output, "4.6\n");
}
	
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}