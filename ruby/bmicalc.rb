# 2015-10-10T17:09+08:00

# Calculate your BMI(Body Mass Index).

require 'ruby_units'


puts """BMI table:
Underweight = < 18.5
Normal weight = 18.5-24.9
Overweight = 25-29.9
Obesity = BMI of 30 or greater
"""
puts '-' * 50

# Get the height and convert it to m
print 'Your height: '
height = Unit.new(gets.chomp).convert_to("m").to_s("%0.2f")

# Get the weight and convert it to kg
print 'Your weight: '
mass = Unit.new(gets.chomp).convert_to("kg").to_s("%0.2f")

puts '-' * 50
bmi = mass.to_f / (height.to_f ** 2)
puts "Height: #{height}\nWeight: #{mass}\nBMI: %0.2f" % bmi


# Dependencies:
# https://github.com/olbrich/ruby-units

# References:
# https://en.wikipedia.org/wiki/Body_mass_index
# http://www.nhlbi.nih.gov/health/educational/lose_wt/BMI/bmicalc.htm