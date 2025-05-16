#include "static_options.hpp"

#include <iostream>

#include "option.hpp"
#include "special.hpp"

namespace ussd
{
	static auto create_consulter_solde_option(Option *&current, bool &is_running) -> Option *
	{
		return new Option("1",
			"Consulter le solde",
			{ new Option("1",
				  "Votre solde est de 1234,56 EUR",
				  [&is_running]
				  {
					  std::cout << "Succès : Votre solde est de 1234,56 EUR\n";
					  is_running = false;
				  }),
				SpecialOption::back(current),
				SpecialOption::root(current),
				SpecialOption::exit(is_running) });
	}

	static auto create_virement_option(Option *&current, bool &is_running) -> Option *
	{
		return new Option("2",
			"Faire un virement",
			{ new Option("1",
				  "Vers un compte interne",
				  { new Option("1",
						"Compte épargne",
						[&is_running]
						{
							std::cout << "Succès : Virement vers compte épargne\n";
							is_running = false;
						}),
					  new Option("2",
						  "Compte courant",
						  [&is_running]
						  {
							  std::cout << "Succès : Virement vers compte courant\n";
							  is_running = false;
						  }),
					  SpecialOption::back(current),
					  SpecialOption::root(current),
					  SpecialOption::exit(is_running) }),
				new Option("2",
					"Vers une autre banque",
					{ new Option("1",
						  "Virement SEPA",
						  [&is_running]
						  {
							  std::cout << "Succès : Virement SEPA effectué\n";
							  is_running = false;
						  }),
						new Option("2",
							"Virement SWIFT",
							[&is_running]
							{
								std::cout << "Succès : Virement SWIFT effectué\n";
								is_running = false;
							}),
						SpecialOption::back(current),
						SpecialOption::root(current),
						SpecialOption::exit(is_running) }),
				SpecialOption::back(current),
				SpecialOption::root(current),
				SpecialOption::exit(is_running) });
	}

	static auto create_parametres_option(Option *&current, bool &is_running) -> Option *
	{
		return new Option("4",
			"Paramètres",
			{ new Option("1",
				  "Changer la langue",
				  [&is_running]
				  {
					  std::cout << "Succès : Langue modifiée\n";
					  is_running = false;
				  }),
				new Option("2",
					"Modifier le code PIN",
					[&is_running]
					{
						std::cout << "Succès : Code PIN modifié\n";
						is_running = false;
					}),
				SpecialOption::back(current),
				SpecialOption::root(current),
				SpecialOption::exit(is_running) });
	}

	static auto create_sos_option(Option *&current, bool &is_running) -> Option *
	{
		return new Option("3",
			"SOS",
			{ new Option("1",
				  "Message SOS",
				  [&is_running]
				  {
					  std::cout << "Succès : Message SOS envoyé\n";
					  is_running = false;
				  }),
				SpecialOption::back(current),
				SpecialOption::root(current),
				SpecialOption::exit(is_running) });
	}

	auto create_root_menu(Option *&current, bool &is_running) -> Option
	{
		return Option("_",
			"Menu Principal",
			{ create_consulter_solde_option(current, is_running),
				create_virement_option(current, is_running),
				create_sos_option(current, is_running),
				create_parametres_option(current, is_running),
				SpecialOption::exit(is_running) });
	}
}  // namespace ussd
