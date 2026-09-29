#!/bin/bash

set -e

INSTALL_DIR="/opt/ticket-system"
SERVICE_NAME="ticket-system"

echo "Installing $SERVICE_NAME..."

sudo mkdir -p "$INSTALL_DIR"

sudo cp ticket-system "$INSTALL_DIR/"
sudo cp -r sql "$INSTALL_DIR/"
sudo cp -r config "$INSTALL_DIR/"

sudo tee "/etc/systemd/system/$SERVICE_NAME.service" > /dev/null <<EOF
[Unit]
Description=Ticket System
After=network.target

[Service]
Type=simple
ExecStart=$INSTALL_DIR/ticket-system
WorkingDirectory=$INSTALL_DIR
Restart=on-failure

[Install]
WantedBy=multi-user.target
EOF

sudo systemctl daemon-reload
sudo systemctl enable "$SERVICE_NAME"
sudo systemctl restart "$SERVICE_NAME"

echo "Done!"