# 2015-10-10T17:09+08:00

# Calculate your BMI(Body Mass Index).

require 'ruby_units'


puts """BMI table:
< 15.0\t\tVery severely underweight
[15.0, 16.0)\tSeverely underweight
[16.0, 18.5)\tUnderweight
[18.5, 25.0)\tNormal (healthy weight)
[25.0, 30.0)\tOverweight
[30.0, 35.0)\tObese Class I (Moderately obese)
[35.0, 40.0)\tObese Class II (Severely obese)
> 40.0\t\tObese Class III (Very severely obese)
"""
puts '-' * 55

# Get the height and convert it to m
print 'Your height: '
height = Unit.new(gets.chomp).convert_to("m").to_s("%0.2f")

# Get the weight and convert it to kg
print 'Your weight: '
mass = Unit.new(gets.chomp).convert_to("kg").to_s("%0.2f")

puts '-' * 55
bmi = mass.to_f / (height.to_f ** 2)
puts "Height: #{height}\nWeight: #{mass}\nBMI: %0.2f" % bmi


# Dependencies:
# https://github.com/olbrich/ruby-units

# References:
# https://en.wikipedia.org/wiki/Body_mass_index
# http://www.nhlbi.nih.gov/health/educational/lose_wt/BMI/bmicalc.htm