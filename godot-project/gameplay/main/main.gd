extends Node2D


var player_hp = 100


func apply_damage(damage):
	player_hp -= damage
	print(player_hp)
	if player_hp <= 0:
		Callable(get_tree(), "reload_current_scene").call_deferred()
