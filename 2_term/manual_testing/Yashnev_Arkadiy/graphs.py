from tkinter import *
from math import *

# Настройка окна
root = Tk()
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
canv = Canvas(root, width=screen_width, height=screen_height, bg='white')
root.state('zoomed')
root.title('')


# Пропорции и конвертер координат
screen_height_middle = screen_height / 2
screen_width_middle = screen_width / 2
 
max_x = 15
min_x = -max_x
def screenX(x):
    return (x - min_x) / (max_x - min_x) * screen_width
 

max_y = floor((screen_height_middle * (max_x - min_x)) / screen_width)
min_y = -max_y
def screenY(y):
    return (y - min_y) / (max_y - min_y) * screen_height


# Отрисовка осей
def draw_axes():
    canv.create_line(0, screen_height_middle, screen_width, screen_height_middle, fill='black', arrow=LAST)
    canv.create_line(screen_width_middle, screen_height, screen_width_middle, 0, fill='black', arrow=LAST)
    for x in range(min_x, max_x+1):
        canv.create_line(screenX(x), screen_height_middle, screenX(x), screen_height_middle + 10, fill='black')
        if x: canv.create_text(screenX(x), screen_height_middle - 15, text=str(round(x, 3)), fill='black')
    for y in range(min_y, max_y+1):
        canv.create_line(screen_width_middle, screenY(y), screen_width_middle + 10, screenY(y), fill='black')
        if y: canv.create_text(screen_width_middle - 15, screenY(-y), text=str(round(y, 3)), fill='black')
    canv.create_text(screen_width_middle + 10, screen_height_middle - 10, text='0', fill='black')
    canv.create_text(screen_width_middle, screen_height_middle, text='•', fill='black')


# Точки
points = []
def draw_points(step):
    funk = funk1+'-'+funk2
    x = min_x
    sign = True
    while x <= max_x:
        y = eval(funk)
        if (y > 0) != sign: points.append(round(x, 3))
        sign = y > 0
        x += step
    offset = 35
    for x in points:
        if x > 0: offset = -35
        y = eval(funk1)
        canv.create_text(screenX(x), screenY(-y), text='•', font=0, fill='black')
        canv.create_text(screenX(x) - offset, screenY(-y) - 10, text=f'x = {x}', fill='black')
        canv.create_text(screenX(x) - offset, screenY(-y) + 5, text=f'y = {round(y, 3)}', fill='black')


# Отрисовка функций
def draw_funks(step):
    counter = 0
    x = min_x
    while x <= max_x:
        first_x = x
        first_y1, first_y2 = eval(funk1), eval(funk2)
        x += step
        second_x = x
        second_y1, second_y2 = eval(funk1), eval(funk2)
        if points[0] <= x <= points[1]:
            if counter % 30 == 0:
                canv.create_line(screenX(x), screenY(-first_y1), screenX(x), screenY(-first_y2), fill='black')
            counter += 1
        canv.create_line(screenX(first_x), screenY(-first_y1), screenX(second_x), screenY(-second_y1), fill='black')
        canv.create_line(screenX(first_x), screenY(-first_y2), screenX(second_x), screenY(-second_y2), fill='black')


# Подсчет площади методом трапеций
def trapezoid_area(step):
    area = 0
    x = points[0]
    while x < points[1]:
        y1 = eval(funk1)
        y2 = eval(funk2)
        x += step
        area += step*(abs(y1-y2)+abs(eval(funk1)-eval(funk2)))/2
    canv.create_text(480, 150, text=f'Площадь методом трапеций ≈ {round(area, 8)}', fill='black')


# Подсчет площади методом средних прямоугольников
def left_rectangle_area(step):
    area = 0
    x = points[0]
    while x < points[1]:
        y1 = eval(funk1)
        y2 = eval(funk2)
        x += step
        area += step*(abs(y1-y2))
    canv.create_text(437, 170, text=f'Площадь методом левых прямоугольников ≈ {round(area, 8)}', fill='black')


# Запуск всех процессов
if __name__ == '__main__':
    funk1 = 'x**2'
    funk2 = '4*cos(x)'
    
    draw_axes()
    draw_points(step=0.0003)
    draw_funks(step=0.005)
    trapezoid_area(step=0.005)
    left_rectangle_area(step=0.005)
    canv.pack()
    
    root.mainloop()
