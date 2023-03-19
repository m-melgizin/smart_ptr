#include "simple_ut.h"
#include "smart_ptr.h"

TEST(ConstructFromRawPointer)
{
    int* raw_ptr = new int(42);
    smart_ptr<int> sp(raw_ptr);

    ASSERT_EQ(*sp, 42);
    ASSERT_EQ((size_t)sp.get(), (size_t)raw_ptr);
}

TEST(CopyConstructor)
{
    smart_ptr<int> sp1(new int(42));
    smart_ptr<int> sp2(sp1);

    ASSERT_EQ(*sp2, 42);
    ASSERT_NE((size_t)sp1.get(), (size_t)sp2.get());
}

TEST(TemplateCopyConstructor)
{
    smart_ptr<int> sp1(new int(42));
    smart_ptr<const int> sp2(sp1);

    ASSERT_EQ(*sp2, 42);
    ASSERT_NE((size_t)sp1.get(), (size_t)sp2.get());
}

TEST(AssignmentOperator)
{
    smart_ptr<int> sp1(new int(42));
    smart_ptr<int> sp2;
    sp2 = sp1;

    ASSERT_EQ(*sp2, 42);
    ASSERT_NE((size_t)sp1.get(), (size_t)sp2.get());
}

TEST(TemplateAssignmentOperator)
{
    smart_ptr<int> sp1(new int(42));
    smart_ptr<const int> sp2;
    sp2 = sp1;

    ASSERT_EQ(*sp2, 42);
    ASSERT_NE((size_t)sp1.get(), (size_t)sp2.get());
}

TEST(DereferenceOperator)
{
    smart_ptr<int> sp(new int(42));

    ASSERT_EQ(*sp, 42);
}

TEST(ArrowOperator)
{
    struct Foo { int x; };
    smart_ptr<Foo> sp(new Foo{42});

    ASSERT_EQ(sp->x, 42);
}

TEST(GetMethod)
{
    int* raw_ptr = new int(42);
    smart_ptr<int> sp(raw_ptr);

    ASSERT_EQ((size_t)sp.get(), (size_t)raw_ptr);
}

TEST(ReleaseMethod)
{
    smart_ptr<int> sp(new int(42));
    int* raw_ptr = sp.release();

    ASSERT_EQ(*raw_ptr, 42);
    ASSERT_EQ((size_t)sp.get(), (size_t)nullptr);
    delete raw_ptr; // need to manually delete the resource
}

TEST(ResetMethod)
{
    smart_ptr<int> sp(new int(42));
    int* raw_ptr = new int(24);
    sp.reset(raw_ptr);

    ASSERT_EQ(*sp, 24);
    ASSERT_EQ((size_t)sp.get(), (size_t)raw_ptr);
}

TEST(ResetMethodWithNullptr)
{
    smart_ptr<int> sp(new int(42));
    sp.reset();

    ASSERT_EQ((size_t)sp.get(), (size_t)nullptr);
}

int main(int argc, char* argv[])
{
    return run_all_tests();
}

/*
==66561== Memcheck, a memory error detector
==66561== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==66561== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==66561== Command: ./main.out
==66561== 
Running test: ConstructFromRawPointer... PASS
Running test: CopyConstructor... PASS
Running test: TemplateCopyConstructor... PASS
Running test: AssignmentOperator... PASS
Running test: TemplateAssignmentOperator... PASS
Running test: DereferenceOperator... PASS
Running test: ArrowOperator... PASS
Running test: GetMethod... PASS
Running test: ReleaseMethod... PASS
Running test: ResetMethod... PASS
Running test: ResetMethodWithNullptr... PASS
Total tests run: 11
Total failures: 0
==66561== 
==66561== HEAP SUMMARY:
==66561==     in use at exit: 0 bytes in 0 blocks
==66561==   total heap usage: 15 allocs, 15 frees, 75,857 bytes allocated
==66561== 
==66561== All heap blocks were freed -- no leaks are possible
==66561== 
==66561== For lists of detected and suppressed errors, rerun with: -s
==66561== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/