s = [0.6896, 0.7071, 0.7001, 0.7049, 0.6297, 0.7139, 0.6925, 0.6819, 0.6316, 0.6299, 0.6013, 0.6444, 0.5889, 0.6125,
     0.5563]
aD = [0.7408, 0.7145, 0.7974, 0.7679, 0.6907, 0.7622, 0.7622, 0.9038, 0.7622, 0.7919, 0.7436, 0.7551, 0.7129, 0.7741,
      0.6595]
for i in range(0, 15) :
    for j in range(0, 15) :
        s = (aD[i] - aD[j]) / aD[i]
        t = (s[i] - s[j]) / s[i]

# random quiz generator
import random

# The quiz data. Keys are states and values are their capitals.
capitals = { 'Alabama' : 'Montgomery', 'Alaska' : 'Juneau', 'Arizona' : 'Phoenix',
             'Arkansas' : 'Little Rock', 'California' : 'Sacramento', 'Colorado' : 'Denver',
             'Connecticut' : 'Hartford', 'Delaware' : 'Dover', 'Florida' : 'Tallahassee',
             'Georgia' : 'Atlanta', 'Hawaii' : 'Honolulu', 'Idaho' : 'Boise', 'Illinois' :
                 'Springfield', 'Indiana' : 'Indianapolis', 'Iowa' : 'Des Moines', 'Kansas' :
                 'Topeka', 'Kentucky' : 'Frankfort', 'Louisiana' : 'Baton Rouge', 'Maine' :
                 'Augusta', 'Maryland' : 'Annapolis', 'Massachusetts' : 'Boston', 'Michigan' :
                 'Lansing', 'Minnesota' : 'Saint Paul', 'Mississippi' : 'Jackson', 'Missouri' :
                 'Jefferson City', 'Montana' : 'Helena', 'Nebraska' : 'Lincoln', 'Nevada' :
                 'Carson City', 'New Hampshire' : 'Concord', 'New Jersey' : 'Trenton', 'NewMexico' : 'Santa Fe',
             'New York' : 'Albany', 'North Carolina' : 'Raleigh',
             'North Dakota' : 'Bismarck', 'Ohio' : 'Columbus', 'Oklahoma' : 'Oklahoma City',
             'Oregon' : 'Salem', 'Pennsylvania' : 'Harrisburg', 'Rhode Island' : 'Providence',
             'South Carolina' : 'Columbia', 'South Dakota' : 'Pierre', 'Tennessee' :
                 'Nashville', 'Texas' : 'Austin', 'Utah' : 'Salt Lake City', 'Vermont' :
                 'Montpelier', 'Virginia' : 'Richmond', 'Washington' : 'Olympia', 'West Virginia' : 'Charleston',
             'Wisconsin' : 'Madison', 'Wyoming' : 'Cheyenne' }
