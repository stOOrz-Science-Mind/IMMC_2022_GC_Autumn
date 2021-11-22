def update:
    time += 0.5
    for i in range(33):
        for j in range(33):
            if roads[i] crosses with roads[j]:
                for k in range(1, num_of_cars + 1_):
                    if car[k] is on roads[i]:
                        if car[k] is accelerating:
                            add the speed of car[k]
                        elif car[k] is decelerating:
                            minus the speed of car[k]
                        if car[k] is at the crossroads (and is about to turn):
                            find the number of crossroad and the status of car[k]
                            choose a random direction to turn to
                            set the turning time of car[k] according to the direction
                        else: #on the road but not crossroad
                            judge whether this car can pass the crossroad (by calculating the least time it would take get to the crossroad)
                            if can_pass crossroad:
                                drive in max_speed
                            else:
                                if distance_to_crossroad <= min_decelerate_dis:
                                    set the deceleration rate as max_decelerate_rate (a constant)
