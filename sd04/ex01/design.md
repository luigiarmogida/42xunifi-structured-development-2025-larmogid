# Expense Tracker – Structured Design Document

## 📋 Overview

This project implements a console-based tool for analyzing personal expenses stored in a CSV-like format. The user provides a file with spending records and can filter the results by category or date range.

## ✅ Functional Requirements

- Read an input file from command line
- Parse lines with format: `YYYY-MM-DD,amount,category,description`
- Gracefully skip invalid lines (log warning)
- Store up to 1000 valid records
- Support filtering:
  - by category (case-insensitive, partial match)
  - by date range (inclusive)
  - or no filtering (show all)
- Show a summary of matching expenses:
  - Count, total, average
  - Breakdown by category (total + percentage)
- Insist on valid user input (dates, ranges, text)
- Exit cleanly and free memory

## 🧱 Data Structures

Defined in `expense_tracker.h`:

- `t_date`: structured date
- `t_expense`: one expense record
- `t_summary`: overall metrics
- `t_category_stat`: per-category breakdown

## 🧩 Modular Design

**parser.h**
- `load_expenses`: reads and validates file
- `parse_line`: converts line to `t_expense`
- `is_valid_*`: helper validators
- `free_expense`: memory cleanup

**filter.h**
- Filtering logic: by category/date/all

**summary.h**
- Aggregates data and prints summary

**utils.h**
- Date comparison, string utilities

## 🧠 Structure Chart

```
main
├── load_expenses
│   └── parse_line
│       ├── is_valid_date
│       ├── is_valid_amount
│       └── trim_whitespace
├── ask_user_filter
│   ├── filter_by_category
│   ├── filter_by_date_range
│   └── filter_all
├── compute_summary
│   └── compute_category_breakdown
└── print_summary
```

## 🔄 Data Flow

```
[input file]
      ↓
 [parser] ───┬──→ [filter]
             │     ↓
             └──→ [summary] → [output]
```

## 🛠️ Libft and Allowed Functions

You may use:
- `malloc`, `free`
- `get_next_line` for file input
- `ft_printf` for output
- Any string/memory helpers from Libft (`ft_split`, `ft_strtrim`, etc.)

## 📎 Notes

- Internally dates are compared lexicographically (`YYYY-MM-DD`)
- Categories are trimmed and normalized for comparison
- Invalid records are not fatal: they are logged and skipped

