#pragma once

#include "../Synthall/Synthall"
#include <wx/wx.h>
#include <exception>

template<class EffectType>
class synEffectInput :public wxChoice {
	std::map<std::string, EffectType*> effects;
	Instrument* destination;
	typename std::vector<EffectType*>::iterator last_effect;
	unsigned int position;
	bool is_set{false};
public:
	synEffectInput(wxWindow* parent, wxWindowID, Instrument* c_destination, wxPoint position = wxDefaultPosition, wxSize = wxDefaultSize);
	~synEffectInput();

	void insert(std::string, EffectType*);
	void erase(std::string);
	void OnChoice(wxCommandEvent&);

	void move_up();
	void move_down();
	unsigned int get_position() {return position;}

	class NameHasAlreadyBeenInserted_exception :public std::exception {
	public:
		const char* what() const noexcept {return "The given name has already been used";}
	};

	class CannotGoHigher_exception :public std::exception {
	public:
		const char* what() const noexcept {return "The effect cannot be moved higher in hierarchy";}
	};

	class CannotGoLower_exception :public std::exception {
	public:
		const char* what() const noexcept {return "The effect cannot be moved lower in hierarchy";}
	};
};

extern template class synEffectInput<SingleSampleEffect>;
extern template class synEffectInput<WholeSampleEffect>;
