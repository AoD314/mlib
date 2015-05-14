
#include <gtest/gtest.h>
#include <mlib/command_line_parser.hpp>

TEST(clp_params, empty)
{
    mlib::Params p("", "", "");
    ASSERT_EQ(false, p.in(""));
}

TEST(clp_params, empty_with_param)
{
    mlib::Params p("a", "", "");
    ASSERT_EQ(false, p.in(""));
}

TEST(clp_params, empty_with_params)
{
    mlib::Params p("a bb", "", "");
    ASSERT_EQ("false", p.get_def());
}

TEST(clp_params, empty_with_def_value)
{
    mlib::Params p("a bb", "11", "");
    ASSERT_EQ("11", p.get_def());
}

TEST(clp_params, has_key)
{
    mlib::Params p("a bb", "11", "");
    ASSERT_EQ(true, p.in("a"));
    ASSERT_EQ(true, p.in("bb"));
    ASSERT_EQ(false, p.in("b"));
}

TEST(clp_params, type_bool)
{
    mlib::Params p("a bb", "true", "");
    ASSERT_EQ(mlib::CMLParamType::BOOL, p.type());
}

TEST(clp_params, type_value)
{
    mlib::Params p(":a bb", "11", "");
    ASSERT_EQ(mlib::CMLParamType::VALUE, p.type());
}

TEST(clp_params, type_number)
{
    mlib::Params p("@a bb", "11", "");
    ASSERT_EQ(mlib::CMLParamType::NUMBER, p.type());
}

TEST(clp_params, type_first)
{
    mlib::Params p(":a -b @d +c", "", "");
    ASSERT_EQ(mlib::CMLParamType::VALUE, p.type());

    std::vector<std::string> ks = p.get_keys();

    ASSERT_EQ(4,    ks.size());
    ASSERT_EQ("a",  ks[0]);
    ASSERT_EQ("-b", ks[1]);
    ASSERT_EQ("d",  ks[2]);
    ASSERT_EQ("+c", ks[3]);
}

TEST(clp_params, get_keys)
{
    mlib::Params p("@a bb +c", "", "");
    std::vector<std::string> ks = p.get_keys();

    ASSERT_EQ(3,    ks.size());
    ASSERT_EQ("a",  ks[0]);
    ASSERT_EQ("bb", ks[1]);
    ASSERT_EQ("+c", ks[2]);
}

TEST(command_line_parser, has_help)
{
    int argc = 2;
    char * argv [] = { "./app", "--help" };
    const std::string keys("{help||help info}");

    mlib::CommandLineParser parser(argc, argv, keys);

    ASSERT_EQ(true, parser.has("help"));
}

TEST(command_line_parser, hasnot_help)
{
    int argc = 1;
    char * argv [] = { "./app" };
    const std::string keys("{help||help info}");

    mlib::CommandLineParser parser(argc, argv, keys);

    ASSERT_EQ(false, parser.has("help"));
}

TEST(command_line_parser, init_parser)
{
    int argc = 1;
    char * argv [] = { "./app" };
    const std::string keys("{.help h||help info}");

    mlib::CommandLineParser parser(argc, argv, keys);

    ASSERT_EQ(false, parser.has("help"));
}

TEST(command_line_parser, empty_keys)
{
    int argc = 2;
    char * argv [] = { "./app", "--usage" };
    const std::string keys("");

    mlib::CommandLineParser parser(argc, argv, keys);

    ASSERT_EQ(true, parser.is_error());
}

TEST(command_line_parser, get_int)
{
    int argc = 1;
    char * argv [] = { "./app" };
    const std::string keys("{:n number|13|this is number}");

    mlib::CommandLineParser parser(argc, argv, keys);

    ASSERT_EQ(13, parser.get<int>("n"));
    ASSERT_EQ(13, parser.get<int>("number"));
}

TEST(command_line_parser, get_int_with_set)
{
    int argc = 3;
    char * argv [] = { "./app", "-n", "11" };
    const std::string keys("{:n number|13|this is number}");

    mlib::CommandLineParser parser(argc, argv, keys);

    ASSERT_EQ(11, parser.get<int>("n"));
    ASSERT_EQ(11, parser.get<int>("number"));
}

TEST(command_line_parser, get_int_with_set_equal)
{
    int argc = 2;
    char * argv [] = { "./app", "-n=9" };
    const std::string keys("{:n number|13|this is number}");

    mlib::CommandLineParser parser(argc, argv, keys);

    ASSERT_EQ(9, parser.get<int>("n"));
    ASSERT_EQ(9, parser.get<int>("number"));
}

TEST(command_line_parser, get_string)
{
    int argc = 3;
    char * argv [] = { "./app", "-n", "11" };
    const std::string keys("{:f file|qqq.txt|path_to_file}");

    mlib::CommandLineParser parser(argc, argv, keys);

    ASSERT_EQ("qqq.txt", parser.get<std::string>("f"));
}

TEST(command_line_parser, set_and_get_string)
{
    int argc = 3;
    char * argv [] = { "./app", "-f", "abc.png" };
    const std::string keys("{:f file|qqq.txt|path_to_file}");

    mlib::CommandLineParser parser(argc, argv, keys);

    ASSERT_EQ("abc.png", parser.get<std::string>("f"));
}

TEST(command_line_parser, get_string_without_set)
{
    int argc = 3;
    char * argv [] = { "./app", "-n", "11" };
    const std::string keys("{:f file||path_to_file}");

    mlib::CommandLineParser parser(argc, argv, keys);

    ASSERT_EQ("", parser.get<std::string>("f"));
}

TEST(command_line_parser, get_string_with_space)
{
    int argc = 3;
    char * argv [] = { "./app", "-m", "hello world!" };
    const std::string keys("{:m ||path_to_file}");

    mlib::CommandLineParser parser(argc, argv, keys);

    ASSERT_EQ("hello world!", parser.get<std::string>("m"));
}
