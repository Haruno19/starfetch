#ifndef CONSTELLATIONS_LIST_H_
#define CONSTELLATIONS_LIST_H_

#include <string>
#include <unordered_map>

inline const std::string res_help_message = R"(
starfetch is a command line tool that displays information about a constellation alongside its scheme.

Usage: starfetch [OPTION] [CONSTELLATION NAME]
    -h      Prints this help message.
    -n      Shows the selected constellation.
    -r      Shows a random constellation.
    -l      Prints the list of all the available constellations.

If launched with no arguments, the behaviour is the same as with '-r'.

Examples:   starfetch -r
            starfetch -n orion
            starfetch
)";

inline const std::string res_template = R"(
┌%0┐
│%1│
│%2│      ^[1;37m%11^[0m
│%3│
│%4│      ^[1;37mQuadrant^[0m: %12
│%5│      ^[1;37mRight ascension^[0m: %13
│%6│      ^[1;37mDeclination^[0m: %14
│%7│      ^[1;37mArea^[0m: %15
│%8│      ^[1;37mMain stars^[0m: %16
│%9│
│%10│
└──────────────────────┘
)";

inline std::unordered_map<std::string, std::string> res_constellations_json_list{
        {"antlia",
         R"(
        {
        "title": "──── ａｎｔｌｉａ ────",
        "graph":
            {
                "line1": { },
                "line2": { },
                "line3": { "15": "✦" },
                "line4": { },
                "line5": { "8":"✦"},
                "line6": { "19": "✦"},
                "line7": { },
                "line8": { "4": "✦" },
                "line9": { },
                "line10": { }
            },
        "name": "Antlia",
        "quadrant": "SQ2",
        "right ascension": "09h 27m 05.1837s to 11h 05m 55.0471s",
        "declination": "-24.5° to -40.4°",
        "area": "239 sq.deg. {62nd}",
        "main stars": "3"
    }
    )"},

        {"apus",
         R"(
    {
        "title": "────── ａｐｕｓ ──────",
        "graph":
            {
                "line1": { },
                "line2": { },
                "line3": { },
                "line4": { "4":"✦"},
                "line5": { "10":"✦"},
                "line6": { "7":"✦"},
                "line7": { "19":"✦"},
                "line8": { },
                "line9": { },
                "line10": { }
            },
        "name": "Apus",
        "quadrant": "SQ3",
        "right ascension":"13h 51m 07.5441s to 18h 27m 27.8395s",
        "declination": "−67.4800797° to −83.1200714°",
        "area": "206 sq.deg. {67th}",
        "main stars": "4"
    }
    )"},

        {"aquarius",
        R"(
        {
        "title": "── ａｑｕａｒｉｕｓ ──",
        "graph":
            {
                "line1": { },
                "line2": { "10": "✦",  "11": "✦" },
                "line3": { "12": "✦",  "15": "✦" },
                "line4": { "4": "✦" },
                "line5": { "6": "✦",  "17": "✦" },
                "line6": { "12": "✦" },
                "line7": { "7": "✦" },
                "line8": { "5": "✦",  "12": "✦" },
                "line9": { "4": "✦",  "19": "✦" },
                "line10": { }
            },
        "name": "Aquarius",
        "quadrant": "SQ4",
        "right ascension": "20h38m to 23h56m",
        "declination": "+3.325° to -24.904°",
        "area": "980 sq.deg. {10th}",
        "main stars": "10, 22"
        }
        )",
        },

        {"ara",
         R"(
        {
            "title": "─────── ａｒａ ───────",
            "graph":
                {
                    "line1": { },
                    "line2": { "4":"✦"},
                    "line3": { "16":"✦"},
                    "line4": { },
                    "line5": { },
                    "line6": { "16":"✦","9":"✦"},
                    "line7": { },
                    "line8": { },
                    "line9": { "19":"✦"},
                    "line10": { "6":"✦"}
                },
            "name": "Ara",
            "quadrant": "SQ3",
            "right ascension":"16h 34m 16.9497s to –18h 10m 41.3407s",
            "declination": "−45.4859734° to −67.6905823°",
            "area": "237 sq.deg. {63rd}",
            "main stars": "8"
        }
    )"},

        {"aries",
         R"(
        {
            "title": "───── ａｒｉｅｓ ─────",
            "graph":
                {
                    "line1": { },
                    "line2": { },
                    "line3": { "5": "✦" },
                    "line4": { },
                    "line5": { "15": "✦" },
                    "line6": { },
                    "line7": { "17": "✦" },
                    "line8": { "16": "✦" },
                    "line9": { },
                    "line10": { }
                },
            "name": "Aries",
            "quadrant": "NQ1",
            "right ascension": "01h 46m 37.3761s to –03h 29m 42.4003s",
            "declination": "+31.2213154° to –10.3632069°",
            "area": "441 sq.deg. {39th}",
            "main stars": "4, 9"
        }
    )"},

        {"bootes",
         R"(
        {
            "title": "──── ｂｏｏｔｅｓ ────",
            "graph":
                {
                    "line1": { },
                    "line2": { "7":"✦"},
                    "line3": { "12":"✦"},
                    "line4": { "4":"✦"},
                    "line5": { "12":"✦"},
                    "line6": { "8":"✦"},
                    "line7": { },
                    "line8": { "13":"✦"},
                    "line9": { "8":"✦", "17":"✦"},
                    "line10": { "7":"✦", "18":"✦"}
                },
            "name": "Boötes",
            "quadrant": "NQ3",
            "right ascension":"13h 36.1m to 15h 49.3m",
            "declination": "+7.36° to +55.1°",
            "area": "907 sq.deg. {13th}",
            "main stars": "7, 15"
        }
        )"},

        {"cancer",
         R"(
        {
            "title": "──── ｃａｎｃｅｒ ────",
            "graph":
                {
                    "line1": { },
                    "line2": { "7": "✦" },
                    "line3": { },
                    "line4": { "10": "✦" },
                    "line5": { "11": "✦" },
                    "line6": { },
                    "line7": { "17": "✦" },
                    "line8": { "8": "✦" },
                    "line9": { },
                    "line10": { }
                },
            "name": "Cancer",
            "quadrant": "NQ1",
            "right ascension": "07h 55m 19.7973s to –09h 22m 35.0364s",
            "declination": "+33.1415138° to –6.4700689°",
            "area": "506 sq.deg. {31st}",
            "main stars": "5"
        }
        )"},

        {"capricorn",
         R"(
        {
            "title": "─ ｃａｐｒｉｃｏｒｎ ─",
            "graph":
                {
                    "line1": { },
                    "line2": { },
                    "line3": { "3": "✦", "19": "✦" },
                    "line4": { "5": "✦", "8": "✦", "12": "✦", "18": "✦" },
                    "line5": { "17": "✦" },
                    "line6": { "5": "✦" },
                    "line7": { "7": "✦", "14": "✦" },
                    "line8": { "12": "✦" },
                    "line9": { },
                    "line10": { }
                },
            "name": "Capricorn",
            "quadrant": "SQ4",
            "right ascension": "20h 06m 46.4871s to 21h 59m 04.8693s",
            "declination": "−8.4043999° to −27.6914144°",
            "area": "414 sq.deg. {40th}",
            "main stars": "9, 13, 23"
        }
        )"},

        {"cassiopeia",
         R"(
        {
            "title": " ｃａｓｓｉｏｐｅｉａ ",
            "graph":
                {
                    "line1": { },
                    "line2": { },
                    "line3": { "4": "✦"},
                    "line4": { },
                    "line5": { "7": "✦", "12": "✦" },
                    "line6": { "20": "✦" },
                    "line7": { },
                    "line8": { "16": "✦" },
                    "line9": { },
                    "line10": { }
                },
            "name": "Cassiopeia",
            "quadrant": "NQ1",
            "right ascension": "22h 57m 04.5897s to –03h 41m 14.0997s",
            "declination": "+77.6923447° to +48.6632690°",
            "area": "598 sq.deg. {25th}",
            "main stars": "5"
        }
        )"},

        {"corona_borealis",
         R"(
        {
            "title": "ｃｒ  ｂｏｒｅａｌｉｓ",
            "graph":
                {
                    "line1": { },
                    "line2": { },
                    "line3": { "15": "✦"},
                    "line4": { },
                    "line5": { "3": "✦", "20": "✦" },
                    "line6": { },
                    "line7": { "5": "✦", "18": "✦"},
                    "line8": { "10": "✦", "13": "✦" },
                    "line9": { },
                    "line10": { }
                },
            "name": "Corona Borealis",
            "quadrant": "NQ1",
            "right ascension": "15h 16m 03.8205s to 16h 25m 07.1526s",
            "declination": "+39.7117195° to +25.5380573°",
            "area": "179 sq.deg. {73rd}",
            "main stars": "8"
        }
        )"},

        {"crux",
         R"(
        {
            "title": "────── ａｐｕｓ ──────",
            "graph":
                {
                    "line1": { },
                    "line2": { "10":"✦"},
                    "line3": { },
                    "line4": { "16":"✦"},
                    "line5": { "5":"✦"},
                    "line6": { },
                    "line7": { },
                    "line8": { },
                    "line9": { "13":"✦"},
                    "line10": { }
                },
            "name": "Crux",
            "quadrant": "SQ3",
            "right ascension":"12.5h",
            "declination": "−60°",
            "area": "68 sq.deg. {88th}",
            "main stars": "4"
        }
        )"},

        {"cygnus",
         R"(
        {
            "title": "──── ｃｙｇｎｕｓ ────",
            "graph":
                {
                    "line1": { },
                    "line2": { "18": "✦" },
                    "line3": { "9": "✦" },
                    "line4": { "15": "✦" },
                    "line5": { "11": "✦" },
                    "line6": { },
                    "line7": { "7": "✦", "15": "✦"},
                    "line8": { "4": "✦" },
                    "line9": { "18": "✦" },
                    "line10": { }
                },
            "name": "Cygnus",
            "quadrant": "NQ4",
            "right ascension": "20.62h",
            "declination": "+42.03°",
            "area": "804 sq.deg. {16th}",
            "main stars": "9"
        }
        )"
        },

        {"gemini",
         R"(
        {
            "title": "──── ｇｅｍｉｎｉ ────",
            "graph":
                {
                    "line1": { "7": "✦" },
                    "line2": { "7": "✦", "14": "✦" },
                    "line3": { "4": "✦", "11": "✦", "15": "✦", "19": "✦" },
                    "line4": { },
                    "line5": { "6": "✦" },
                    "line6": { "4": "✦", "8": "✦", "15": "✦" },
                    "line7": { },
                    "line8": { },
                    "line9": { "4": "✦", "8": "✦", "14": "✦", "17": "✦" },
                    "line10": { "18": "✦" }
                },
            "name": "Gemini",
            "quadrant": "NQ2",
            "right ascension": "7h",
            "declination": "+20°",
            "area": "514 sq.deg. {30th}",
            "main stars": "8,17"
        }
        )"},
};


#endif// CONSTELLATIONS_LIST_H_
