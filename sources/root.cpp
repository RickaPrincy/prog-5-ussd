#include "root.hpp"

#include <iostream>

#include "option.hpp"

namespace ussd
{
	auto create_root_menu(bool &is_running) -> Option
	{
		return Option("Menu Principal",
			{
				new Option(
					"Consulter le solde", [] { std::cout << "Votre solde est de 1234,56 EUR\n"; }),
				new Option("Faire un virement",
					{
						new Option("Vers un compte interne",
							{
								new Option("Compte épargne",
									[] { std::cout << "Virement vers compte épargne...\n"; }),
								new Option("Compte courant",
									[] { std::cout << "Virement vers compte courant...\n"; }),
							}),
						new Option("Vers une autre banque",
							{
								new Option("Virement SEPA",
									[] { std::cout << "Virement SEPA en cours...\n"; }),
								new Option("Virement SWIFT",
									[] { std::cout << "Virement SWIFT en cours...\n"; }),
							}),
					}),
				new Option("Recharger le téléphone",
					[] { std::cout << "Rechargement du téléphone en cours...\n"; }),
				new Option("Paramètres",
					{
						new Option(
							"Changer la langue", [] { std::cout << "Changer la langue...\n"; }),
						new Option("Modifier le code PIN",
							[] { std::cout << "Modification du code PIN...\n"; }),
					}),
				new Option("Quitter",
					[&is_running]
					{
						std::cout << "Merci de votre visite, au revoir!\n";
						is_running = false;
					}),
			});
	}
}  // namespace ussd
