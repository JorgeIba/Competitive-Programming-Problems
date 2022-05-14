

months = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]
days_per_month = {"Jan": 31, "Feb": 28, "Mar": 31, "Apr": 30, "May": 31, "Jun": 30, "Jul": 31, "Aug": 31, "Sep": 30, "Oct": 31, "Nov": 30, "Dec": 31}


curr_year = 1900
last_month = 0
total_days = 0
total_sundays = 0
while curr_year < 2001:

    next_month = (last_month + 1) % 12
    total_days += days_per_month[ months[last_month] ]
    if last_month == 1:
        if (curr_year % 4 == 0 and curr_year % 100 != 0) or curr_year % 400 == 0:
            total_days += 1
    
    total_sundays += 1 if total_days % 7 == 6 and curr_year > 1900 else 0

    # if total_days % 7 == 6:
        # pass
        # print(f"Hubo un domingo el dia 1 del mes: {months[next_month]} / {curr_year}" )


    last_month = next_month
    if next_month == 0:
        curr_year += 1


print(total_sundays)